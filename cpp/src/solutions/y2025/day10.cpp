// Advent of Code 2025 - Día 10
#include <algorithm>
#include <climits>
#include <map>

#include "aoc.hpp"

using namespace aoc;

namespace {

struct Maquina {
    std::vector<bool> luces;
    std::vector<std::vector<int>> botones;
    std::vector<int> contadores;
};

// '[.##.] (3) (1,3) ... {3,5,4}' -> luces objetivo, botones y contadores objetivo.
Maquina leer(const std::string& line) {
    Maquina m;
    auto corchete = line.find(']'), llave = line.find('{');
    for (char c : line.substr(1, corchete - 1)) m.luces.push_back(c == '#');
    for (auto p = line.find('(', corchete); p != std::string::npos && p < llave; p = line.find('(', p)) {
        auto q = line.find(')', p);
        std::vector<int> boton;
        for (auto n : ints(line.substr(p + 1, q - p - 1))) boton.push_back(static_cast<int>(n));
        m.botones.push_back(boton);
        p = q;
    }
    for (auto n : ints(line.substr(llave))) m.contadores.push_back(static_cast<int>(n));
    return m;
}

using Patrones = std::map<std::vector<int>, int>;

// Para cada combinación de botones (cada uno 0 o 1 veces): incremento de cada contador -> mínimo de pulsaciones.
Patrones patrones(const std::vector<std::vector<int>>& botones, std::size_t n) {
    Patrones mejor;
    for (unsigned seleccion = 0; seleccion < (1u << botones.size()); ++seleccion) {
        std::vector<int> incremento(n, 0);
        for (std::size_t j = 0; j < botones.size(); ++j)
            if (seleccion >> j & 1)
                for (int i : botones[j]) ++incremento[i];
        int pulsaciones = __builtin_popcount(seleccion);
        auto [it, nuevo] = mejor.try_emplace(incremento, pulsaciones);
        if (!nuevo) it->second = std::min(it->second, pulsaciones);
    }
    return mejor;
}

// Truco de la mitad: tras elegir una combinación con la misma paridad, el resto se pulsa por pares.
long long minimo(const std::vector<int>& actual, const Patrones& pats, std::map<std::vector<int>, long long>& memo) {
    if (std::all_of(actual.begin(), actual.end(), [](int v) { return v == 0; })) return 0;
    if (auto it = memo.find(actual); it != memo.end()) return it->second;

    long long mejor = LLONG_MAX;
    for (const auto& [inc, pulsaciones] : pats) {
        bool valido = true;
        for (std::size_t i = 0; i < actual.size() && valido; ++i) valido = inc[i] <= actual[i] && (actual[i] - inc[i]) % 2 == 0;
        if (!valido) continue;
        std::vector<int> mitad(actual.size());
        for (std::size_t i = 0; i < actual.size(); ++i) mitad[i] = (actual[i] - inc[i]) / 2;
        long long sub = minimo(mitad, pats, memo);
        if (sub != LLONG_MAX) mejor = std::min(mejor, pulsaciones + 2 * sub);
    }
    return memo[actual] = mejor;
}

bool vacia(const std::string& s) { return s.find_first_not_of(" \t\r") == std::string::npos; }

Answer part1(const Lines& lines) {
    long long total = 0;
    for (const auto& line : lines) {
        if (vacia(line)) continue;
        auto m = leer(line);
        // solo importa la paridad de cada luz: se busca la combinación con esa paridad y menos pulsaciones
        int mejor = INT_MAX;
        for (const auto& [inc, pulsaciones] : patrones(m.botones, m.luces.size())) {
            bool coincide = true;
            for (std::size_t i = 0; i < inc.size(); ++i) coincide &= (inc[i] % 2 == 1) == m.luces[i];
            if (coincide) mejor = std::min(mejor, pulsaciones);
        }
        total += mejor;
    }
    return ans(total);
}

Answer part2(const Lines& lines) {
    long long total = 0;
    for (const auto& line : lines) {
        if (vacia(line)) continue;
        auto m = leer(line);
        std::map<std::vector<int>, long long> memo;
        total += minimo(m.contadores, patrones(m.botones, m.contadores.size()), memo);
    }
    return ans(total);
}

}  // namespace

AOC_REGISTER(2025, 10, part1, part2);
