// Advent of Code 2015 - Día 8
#include <algorithm>

#include "aoc.hpp"

using namespace aoc;

namespace {

// Caracteres del valor de un literal: cada escape (\\, \", \xNN) cuenta como uno; las comillas exteriores no cuentan.
std::size_t en_memoria(const std::string& literal) {
    std::string c = literal.substr(1, literal.size() - 2);
    std::size_t i = 0, n = 0;
    while (i < c.size()) {
        i += c[i] == '\\' ? (c[i + 1] == 'x' ? 4 : 2) : 1;
        ++n;
    }
    return n;
}

// Caracteres de la cadena codificada de nuevo: comillas exteriores y \ y " escapadas.
std::size_t codificado(const std::string& literal) {
    return literal.size() + 2 + std::count_if(literal.begin(), literal.end(), [](char c) { return c == '\\' || c == '"'; });
}

std::vector<std::string> literales(const Lines& lines) {
    std::vector<std::string> out;
    for (auto l : lines) {
        l.erase(l.find_last_not_of(" \t\r") + 1);
        if (!l.empty()) out.push_back(l);
    }
    return out;
}

Answer part1(const Lines& lines) {
    long long total = 0;
    for (const auto& l : literales(lines)) total += l.size() - en_memoria(l);
    return ans(total);
}

Answer part2(const Lines& lines) {
    long long total = 0;
    for (const auto& l : literales(lines)) total += codificado(l) - l.size();
    return ans(total);
}

}  // namespace

AOC_REGISTER(2015, 8, part1, part2);
