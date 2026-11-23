// Advent of Code 2015 - Día 14
#include <algorithm>
#include <array>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr long long CARRERA = 2503;         // segundos de la carrera
constexpr long long CARRERA_EJEMPLO = 1000;  // el ejemplo del enunciado (2 renos) dura 1000 s

using Reno = std::array<long long, 3>;  // velocidad, segundos volando, segundos descansando

std::vector<Reno> leer(const Lines& lines) {
    std::vector<Reno> renos;
    for (const auto& l : lines) {
        auto n = ints(l);
        if (n.size() >= 3) renos.push_back({n[0], n[1], n[2]});
    }
    return renos;
}

long long distancia(const Reno& r, long long segundos) {
    long long ciclos = segundos / (r[1] + r[2]), resto = segundos % (r[1] + r[2]);
    return r[0] * (ciclos * r[1] + std::min(resto, r[1]));
}

long long duracion(const std::vector<Reno>& renos) { return renos.size() <= 2 ? CARRERA_EJEMPLO : CARRERA; }

Answer part1(const Lines& lines) {
    auto renos = leer(lines);
    long long mejor = 0;
    for (const auto& r : renos) mejor = std::max(mejor, distancia(r, duracion(renos)));
    return ans(mejor);
}

// cada segundo, el reno (o renos) que va en cabeza gana un punto
Answer part2(const Lines& lines) {
    auto renos = leer(lines);
    std::vector<long long> puntos(renos.size(), 0);
    for (long long s = 1; s <= duracion(renos); ++s) {
        std::vector<long long> d;
        for (const auto& r : renos) d.push_back(distancia(r, s));
        long long maxima = *std::max_element(d.begin(), d.end());
        for (std::size_t i = 0; i < d.size(); ++i) puntos[i] += d[i] == maxima;
    }
    return ans(*std::max_element(puntos.begin(), puntos.end()));
}

}  // namespace

AOC_REGISTER(2015, 14, part1, part2);
