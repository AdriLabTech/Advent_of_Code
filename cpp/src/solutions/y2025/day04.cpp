// Advent of Code 2025 - Día 4
#include <set>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Rollo = std::pair<int, int>;

std::set<Rollo> leer_rollos(const Lines& lines) {
    std::set<Rollo> rollos;
    for (std::size_t r = 0; r < lines.size(); ++r)
        for (std::size_t c = 0; c < lines[r].size(); ++c)
            if (lines[r][c] == '@') rollos.insert({int(r), int(c)});
    return rollos;
}

// Rollos con menos de 4 rollos vecinos.
std::vector<Rollo> accesibles(const std::set<Rollo>& rollos) {
    std::vector<Rollo> out;
    for (auto [r, c] : rollos) {
        int vecinos = 0;
        for (int dr = -1; dr <= 1; ++dr)
            for (int dc = -1; dc <= 1; ++dc) vecinos += (dr || dc) && rollos.count({r + dr, c + dc});
        if (vecinos < 4) out.push_back({r, c});
    }
    return out;
}

Answer part1(const Lines& lines) { return ans(accesibles(leer_rollos(lines)).size()); }

Answer part2(const Lines& lines) {
    auto rollos = leer_rollos(lines);
    std::size_t quitados = 0;
    for (auto retirar = accesibles(rollos); !retirar.empty(); retirar = accesibles(rollos)) {  // hasta que no quede ninguno accesible
        for (const auto& r : retirar) rollos.erase(r);
        quitados += retirar.size();
    }
    return ans(quitados);
}

}  // namespace

AOC_REGISTER(2025, 4, part1, part2);
