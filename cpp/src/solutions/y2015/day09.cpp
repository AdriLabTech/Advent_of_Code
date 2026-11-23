// Advent of Code 2015 - Día 9
#include <algorithm>
#include <climits>
#include <map>
#include <sstream>

#include "aoc.hpp"

using namespace aoc;

namespace {

// (ruta más corta, ruta más larga) que visitan todas las ciudades exactamente una vez (hay pocas: se prueban todas).
std::pair<int, int> rutas(const Lines& lines) {
    std::map<std::string, int> ids;
    auto id = [&](const std::string& c) { return ids.emplace(c, static_cast<int>(ids.size())).first->second; };
    std::vector<std::array<int, 3>> tramos;
    for (const auto& l : lines) {
        auto igual = l.find(" = "), to = l.find(" to ");
        if (igual == std::string::npos) continue;
        int a = id(l.substr(0, to)), b = id(l.substr(to + 4, igual - to - 4));
        tramos.push_back({a, b, std::stoi(l.substr(igual + 3))});
    }
    int n = static_cast<int>(ids.size());
    std::vector<std::vector<int>> d(n, std::vector<int>(n, 0));
    for (auto& [a, b, v] : tramos) d[a][b] = d[b][a] = v;

    int minimo = INT_MAX, maximo = 0;
    std::function<void(int, unsigned, int)> recorrer = [&](int actual, unsigned visitadas, int recorrido) {
        if (__builtin_popcount(visitadas) == n) {
            minimo = std::min(minimo, recorrido);
            maximo = std::max(maximo, recorrido);
            return;
        }
        for (int s = 0; s < n; ++s)
            if (!(visitadas >> s & 1)) recorrer(s, visitadas | 1u << s, recorrido + d[actual][s]);
    };
    for (int inicio = 0; inicio < n; ++inicio) recorrer(inicio, 1u << inicio, 0);
    return {minimo, maximo};
}

Answer part1(const Lines& lines) { return ans(rutas(lines).first); }

Answer part2(const Lines& lines) { return ans(rutas(lines).second); }

}  // namespace

AOC_REGISTER(2015, 9, part1, part2);
