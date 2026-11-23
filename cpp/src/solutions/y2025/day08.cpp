// Advent of Code 2025 - Día 8
#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <tuple>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int CONEXIONES = 1000;        // pares más cercanos que se conectan en la parte 1
constexpr int CONEXIONES_EJEMPLO = 10;  // el ejemplo del enunciado (20 cajas) conecta solo 10

using Caja = std::array<long long, 3>;

struct Circuitos {
    std::vector<int> padre, tamano;

    explicit Circuitos(int n) : padre(n), tamano(n, 1) { std::iota(padre.begin(), padre.end(), 0); }

    int raiz(int i) {
        while (padre[i] != i) i = padre[i] = padre[padre[i]];
        return i;
    }

    // Une los circuitos de i y j. Devuelve false si ya estaban unidos.
    bool unir(int i, int j) {
        int ri = raiz(i), rj = raiz(j);
        if (ri == rj) return false;
        if (tamano[ri] < tamano[rj]) std::swap(ri, rj);
        padre[rj] = ri;
        tamano[ri] += tamano[rj];
        return true;
    }
};

std::vector<Caja> leer(const Lines& lines) {
    std::vector<Caja> cajas;
    for (const auto& l : lines)
        if (l.find_first_not_of(" \t\r") != std::string::npos) {
            auto v = ints(l);
            cajas.push_back({v[0], v[1], v[2]});
        }
    return cajas;
}

// Recorre los pares por distancia creciente (Kruskal) y une los circuitos de cada par.
// Se detiene tras limite_pares pares (cuenten o no como unión; -1 = sin límite) o al quedar un solo circuito.
// Devuelve (tamaños de los circuitos, último par que unió dos circuitos distintos).
std::pair<std::vector<long long>, std::pair<int, int>> conectar(const std::vector<Caja>& cajas, long long limite_pares) {
    int n = static_cast<int>(cajas.size());
    std::vector<std::tuple<long long, int, int>> pares;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {
            long long d = 0;
            for (int k = 0; k < 3; ++k) d += (cajas[i][k] - cajas[j][k]) * (cajas[i][k] - cajas[j][k]);
            pares.emplace_back(d, i, j);
        }
    std::sort(pares.begin(), pares.end());

    Circuitos c(n);
    int circuitos = n;
    std::pair<int, int> ultimo{0, 0};
    for (std::size_t visitados = 0; visitados < pares.size(); ++visitados) {
        if (static_cast<long long>(visitados) == limite_pares || circuitos == 1) break;
        auto [_, i, j] = pares[visitados];
        if (c.unir(i, j)) {  // si ya estaban en el mismo circuito no pasa nada
            --circuitos;
            ultimo = {i, j};
        }
    }
    std::vector<long long> tamanos;
    for (int i = 0; i < n; ++i)
        if (c.padre[i] == i) tamanos.push_back(c.tamano[i]);
    return {tamanos, ultimo};
}

Answer part1(const Lines& lines) {
    auto cajas = leer(lines);
    auto [tamanos, _] = conectar(cajas, cajas.size() <= 20 ? CONEXIONES_EJEMPLO : CONEXIONES);
    std::sort(tamanos.begin(), tamanos.end(), std::greater<>());
    long long producto = 1;
    for (std::size_t i = 0; i < tamanos.size() && i < 3; ++i) producto *= tamanos[i];
    return ans(producto);
}

Answer part2(const Lines& lines) {
    auto cajas = leer(lines);
    auto [_, ultimo] = conectar(cajas, -1);  // la última unión es la que deja un solo circuito
    return ans(cajas[ultimo.first][0] * cajas[ultimo.second][0]);
}

}  // namespace

AOC_REGISTER(2025, 8, part1, part2);
