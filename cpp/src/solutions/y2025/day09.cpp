// Advent of Code 2025 - Día 9
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <set>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Punto = std::pair<long long, long long>;

std::vector<Punto> leer(const Lines& lines) {
    std::vector<Punto> puntos;
    for (const auto& l : lines)
        if (l.find_first_not_of(" \t\r") != std::string::npos) {
            auto v = ints(l);
            puntos.push_back({v[0], v[1]});
        }
    return puntos;
}

long long area(const Punto& a, const Punto& b) { return (std::llabs(a.first - b.first) + 1) * (std::llabs(a.second - b.second) + 1); }

// Posición de un valor en la lista ordenada de coordenadas usadas.
int indice(const std::vector<long long>& v, long long x) { return static_cast<int>(std::lower_bound(v.begin(), v.end(), x) - v.begin()); }

Answer part1(const Lines& lines) {
    auto lista = leer(lines);
    std::set<Punto> unicos(lista.begin(), lista.end());
    std::vector<Punto> puntos(unicos.begin(), unicos.end());
    long long mejor = 0;
    for (std::size_t i = 0; i < puntos.size(); ++i)
        for (std::size_t j = i + 1; j < puntos.size(); ++j) mejor = std::max(mejor, area(puntos[i], puntos[j]));
    return ans(mejor);
}

Answer part2(const Lines& lines) {
    auto rojas = leer(lines);
    int n = static_cast<int>(rojas.size());

    // 1) Compresión de coordenadas: solo importan los valores usados (y sus vecinos, para tener borde exterior)
    std::set<long long> sx, sy;
    for (auto& [x, y] : rojas)
        for (int d = -1; d <= 1; ++d) {
            sx.insert(x + d);
            sy.insert(y + d);
        }
    std::vector<long long> xs(sx.begin(), sx.end()), ys(sy.begin(), sy.end());
    int alto = static_cast<int>(ys.size()), ancho = static_cast<int>(xs.size());

    // 2) Borde del polígono (los lados unen cada punto con el siguiente)
    std::vector<std::vector<char>> borde(alto, std::vector<char>(ancho, 0)), exterior = borde;
    for (int k = 0; k < n; ++k) {
        auto &a = rojas[k], &b = rojas[(k + 1) % n];
        int x1 = indice(xs, a.first), x2 = indice(xs, b.first), y1 = indice(ys, a.second), y2 = indice(ys, b.second);
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
            for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x) borde[y][x] = 1;
    }

    // 3) Relleno desde fuera: lo que no se alcanza está dentro del polígono
    std::queue<std::pair<int, int>> cola;
    for (int y = 0; y < alto; ++y)
        for (int x = 0; x < ancho; ++x)
            if ((y == 0 || y == alto - 1 || x == 0 || x == ancho - 1) && !borde[y][x]) {
                exterior[y][x] = 1;
                cola.push({y, x});
            }
    while (!cola.empty()) {
        auto [y, x] = cola.front();
        cola.pop();
        for (auto [dy, dx] : {std::pair{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            int ny = y + dy, nx = x + dx;
            if (ny >= 0 && ny < alto && nx >= 0 && nx < ancho && !borde[ny][nx] && !exterior[ny][nx]) {
                exterior[ny][nx] = 1;
                cola.push({ny, nx});
            }
        }
    }

    // 4) Sumas acumuladas 2D de las celdas permitidas (borde o interior)
    std::vector<std::vector<int>> suma(alto + 1, std::vector<int>(ancho + 1, 0));
    for (int y = 0; y < alto; ++y)
        for (int x = 0; x < ancho; ++x)
            suma[y + 1][x + 1] = suma[y][x + 1] + suma[y + 1][x] - suma[y][x] + (borde[y][x] || !exterior[y][x]);

    // 5) Mayor rectángulo cuyas celdas están todas permitidas
    long long mejor = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            long long a = area(rojas[i], rojas[j]);
            if (a <= mejor) continue;
            int x1 = std::min(indice(xs, rojas[i].first), indice(xs, rojas[j].first));
            int x2 = std::max(indice(xs, rojas[i].first), indice(xs, rojas[j].first));
            int y1 = std::min(indice(ys, rojas[i].second), indice(ys, rojas[j].second));
            int y2 = std::max(indice(ys, rojas[i].second), indice(ys, rojas[j].second));
            int dentro = suma[y2 + 1][x2 + 1] - suma[y1][x2 + 1] - suma[y2 + 1][x1] + suma[y1][x1];
            if (dentro == (x2 - x1 + 1) * (y2 - y1 + 1)) mejor = a;
        }
    return ans(mejor);
}

}  // namespace

AOC_REGISTER(2025, 9, part1, part2);
