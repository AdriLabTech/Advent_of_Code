// Advent of Code 2015 - Día 21
#include <algorithm>
#include <array>
#include <climits>
#include <numeric>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Item = std::array<long long, 3>;  // coste, daño, armadura

const std::vector<Item> ARMAS = {{8, 4, 0}, {10, 5, 0}, {25, 6, 0}, {40, 7, 0}, {74, 8, 0}};
const std::vector<Item> ARMADURAS = {{0, 0, 0}, {13, 0, 1}, {31, 0, 2}, {53, 0, 3}, {75, 0, 4}, {102, 0, 5}};  // la primera = sin armadura
const std::vector<Item> ANILLOS = {{25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, {80, 0, 3}};

// Gana quien tarda menos turnos en matar al otro (el jugador pega primero, así que gana en un empate).
bool gana_jugador(long long vida, long long dano, long long armadura, const std::vector<long long>& jefe) {
    long long da = std::max(1LL, dano - jefe[2]), db = std::max(1LL, jefe[1] - armadura);
    return (jefe[0] + da - 1) / da <= (vida + db - 1) / db;
}

// (coste, daño, armadura) de cada compra posible: 1 arma, 0-1 armadura y 0-2 anillos.
std::vector<Item> equipamientos() {
    std::vector<std::vector<Item>> anillos{{}};
    for (std::size_t i = 0; i < ANILLOS.size(); ++i) {
        anillos.push_back({ANILLOS[i]});
        for (std::size_t j = i + 1; j < ANILLOS.size(); ++j) anillos.push_back({ANILLOS[i], ANILLOS[j]});
    }
    std::vector<Item> out;
    for (const auto& arma : ARMAS)
        for (const auto& armadura : ARMADURAS)
            for (const auto& par : anillos) {
                Item total{arma[0] + armadura[0], arma[1] + armadura[1], arma[2] + armadura[2]};
                for (const auto& a : par)
                    for (int k = 0; k < 3; ++k) total[k] += a[k];
                out.push_back(total);
            }
    return out;
}

std::vector<long long> leer_jefe(const Lines& lines) {
    std::string todo;
    for (const auto& l : lines) todo += l + " ";
    return ints(todo);
}

Answer part1(const Lines& lines) {
    auto jefe = leer_jefe(lines);
    long long mejor = LLONG_MAX;
    for (const auto& e : equipamientos())
        if (gana_jugador(100, e[1], e[2], jefe)) mejor = std::min(mejor, e[0]);
    return ans(mejor);
}

Answer part2(const Lines& lines) {
    auto jefe = leer_jefe(lines);
    long long mejor = 0;
    for (const auto& e : equipamientos())
        if (!gana_jugador(100, e[1], e[2], jefe)) mejor = std::max(mejor, e[0]);
    return ans(mejor);
}

}  // namespace

AOC_REGISTER(2015, 21, part1, part2);
