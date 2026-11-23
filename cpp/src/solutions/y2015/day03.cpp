// Advent of Code 2015 - Día 3
#include <set>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

// Los repartidores se turnan: el movimiento i lo hace el repartidor i % repartidores.
std::size_t casas_visitadas(const std::string& ruta, std::size_t repartidores) {
    std::vector<std::pair<int, int>> posiciones(repartidores, {0, 0});
    std::set<std::pair<int, int>> visitadas{{0, 0}};
    for (std::size_t i = 0; i < ruta.size(); ++i) {
        int dx = 0, dy = 0;
        switch (ruta[i]) {
            case '^': dy = 1; break;
            case 'v': dy = -1; break;
            case '>': dx = 1; break;
            case '<': dx = -1; break;
            default: continue;
        }
        auto& p = posiciones[i % repartidores];
        p = {p.first + dx, p.second + dy};
        visitadas.insert(p);
    }
    return visitadas.size();
}

Answer part1(const Lines& lines) { return ans(casas_visitadas(lines.at(0), 1)); }

Answer part2(const Lines& lines) { return ans(casas_visitadas(lines.at(0), 2)); }

}  // namespace

AOC_REGISTER(2015, 3, part1, part2);
