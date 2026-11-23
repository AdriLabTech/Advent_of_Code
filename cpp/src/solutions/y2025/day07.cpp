// Advent of Code 2025 - Día 7
#include <set>
#include <tuple>

#include "aoc.hpp"

using namespace aoc;

namespace {

std::tuple<Lines, std::size_t, std::size_t> leer(const Lines& lines) {
    Lines mapa;
    for (const auto& l : lines)
        if (!l.empty()) mapa.push_back(l);
    for (std::size_t y = 0; y < mapa.size(); ++y) {
        auto x = mapa[y].find('S');
        if (x != std::string::npos) return {mapa, y, x};
    }
    throw std::runtime_error("no hay S");
}

Answer part1(const Lines& lines) {
    auto [mapa, sy, sx] = leer(lines);
    std::size_t ancho = mapa[0].size();
    std::set<std::size_t> rayos{sx};
    long long divisiones = 0;
    for (std::size_t y = sy; y + 1 < mapa.size(); ++y) {  // el rayo baja fila a fila
        std::set<std::size_t> siguiente;
        for (std::size_t x : rayos) {
            if (mapa[y + 1][x] == '^') {  // divisor: sale por los dos lados
                ++divisiones;
                if (x > 0) siguiente.insert(x - 1);
                if (x + 1 < ancho) siguiente.insert(x + 1);
            } else {
                siguiente.insert(x);
            }
        }
        rayos = siguiente;
    }
    return ans(divisiones);
}

Answer part2(const Lines& lines) {
    auto [mapa, sy, sx] = leer(lines);
    std::size_t ancho = mapa[0].size();
    // caminos[x]: líneas temporales que salen por abajo partiendo de (x, y); se rellena de abajo arriba
    std::vector<unsigned __int128> caminos(ancho, 1);
    for (std::size_t y = mapa.size() - 1; y-- > sy;) {
        std::vector<unsigned __int128> nuevo(ancho);
        for (std::size_t x = 0; x < ancho; ++x)
            nuevo[x] = mapa[y + 1][x] == '^' ? (x > 0 ? caminos[x - 1] : 0) + (x + 1 < ancho ? caminos[x + 1] : 0) : caminos[x];
        caminos = nuevo;
    }
    return ans(caminos[sx]);
}

}  // namespace

AOC_REGISTER(2025, 7, part1, part2);
