// Advent of Code 2015 - Día 7
#include <cstdint>
#include <map>
#include <sstream>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Gates = std::map<std::string, std::vector<std::string>>;

Gates leer(const Lines& lines) {
    Gates gates;
    for (const auto& l : lines) {
        auto flecha = l.find(" -> ");
        if (flecha == std::string::npos) continue;
        std::stringstream ss(l.substr(0, flecha));
        std::vector<std::string> origen;
        for (std::string t; ss >> t;) origen.push_back(t);
        std::string destino = l.substr(flecha + 4);
        destino.erase(destino.find_last_not_of(" \t\r") + 1);
        gates[destino] = origen;
    }
    return gates;
}

// Señal de un cable (o número). `forzado` sustituye la señal de un cable.
std::uint16_t valor(const std::string& token, const Gates& gates, std::map<std::string, std::uint16_t>& memo, const std::pair<std::string, std::uint16_t>* forzado) {
    if (std::isdigit(static_cast<unsigned char>(token[0]))) return static_cast<std::uint16_t>(std::stoi(token));
    if (forzado && forzado->first == token) return forzado->second;
    if (auto it = memo.find(token); it != memo.end()) return it->second;
    const auto& g = gates.at(token);
    std::uint16_t r;
    if (g.size() == 1) r = valor(g[0], gates, memo, forzado);                                   // 123 -> x  /  a -> b
    else if (g.size() == 2) r = static_cast<std::uint16_t>(~valor(g[1], gates, memo, forzado));  // NOT x
    else {
        std::uint16_t a = valor(g[0], gates, memo, forzado), b = valor(g[2], gates, memo, forzado);
        r = g[1] == "AND" ? a & b : g[1] == "OR" ? a | b : g[1] == "LSHIFT" ? static_cast<std::uint16_t>(a << b) : static_cast<std::uint16_t>(a >> b);
    }
    return memo[token] = r;
}

// el ejemplo del enunciado no tiene cable a
Answer part1(const Lines& lines) {
    auto gates = leer(lines);
    if (!gates.count("a")) return std::nullopt;
    std::map<std::string, std::uint16_t> memo;
    return ans(valor("a", gates, memo, nullptr));
}

// la señal de a (parte 1) se pasa al cable b y se recalcula todo
Answer part2(const Lines& lines) {
    auto gates = leer(lines);
    if (!gates.count("a")) return std::nullopt;
    std::map<std::string, std::uint16_t> memo1, memo2;
    std::pair<std::string, std::uint16_t> b{"b", valor("a", gates, memo1, nullptr)};
    return ans(valor("a", gates, memo2, &b));
}

}  // namespace

AOC_REGISTER(2015, 7, part1, part2);
