// Advent of Code 2015 - Día 10
#include "aoc.hpp"

using namespace aoc;

namespace {

// Cada tanda de dígitos iguales se sustituye por (cuántos)(qué dígito).
std::size_t mirar_y_decir(std::string actual, int veces) {
    for (int v = 0; v < veces; ++v) {
        std::string siguiente;
        siguiente.reserve(actual.size() * 2);
        for (std::size_t i = 0, j; i < actual.size(); i = j) {
            j = i;
            while (j < actual.size() && actual[j] == actual[i]) ++j;
            siguiente += std::to_string(j - i);
            siguiente += actual[i];
        }
        actual = std::move(siguiente);
    }
    return actual.size();
}

std::string primera(const Lines& lines) {
    std::string s = lines.at(0);
    s.erase(s.find_last_not_of(" \t\r") + 1);
    return s;
}

Answer part1(const Lines& lines) { return ans(mirar_y_decir(primera(lines), 40)); }

Answer part2(const Lines& lines) { return ans(mirar_y_decir(primera(lines), 50)); }

}  // namespace

AOC_REGISTER(2015, 10, part1, part2);
