// Advent of Code 2015 - Día 17
#include <algorithm>
#include <numeric>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int LITROS = 150;
constexpr int LITROS_EJEMPLO = 25;  // el ejemplo del enunciado (5 contenedores) guarda 25 litros

// formas[n] = de cuántas maneras se llenan exactamente los litros con n contenedores (programación dinámica).
std::vector<long long> formas_por_cantidad(const Lines& lines) {
    std::vector<int> contenedores;
    for (const auto& l : lines)
        if (l.find_first_not_of(" \t\r") != std::string::npos) contenedores.push_back(std::stoi(l));
    int litros = contenedores.size() <= 5 ? LITROS_EJEMPLO : LITROS;
    int n = static_cast<int>(contenedores.size());
    // tabla[k][s]: subconjuntos de k contenedores que suman s litros
    std::vector<std::vector<long long>> tabla(n + 1, std::vector<long long>(litros + 1, 0));
    tabla[0][0] = 1;
    for (int c : contenedores)
        for (int k = n - 1; k >= 0; --k)
            for (int s = litros - c; s >= 0; --s) tabla[k + 1][s + c] += tabla[k][s];
    std::vector<long long> formas;
    for (const auto& fila : tabla) formas.push_back(fila[litros]);
    return formas;
}

Answer part1(const Lines& lines) {
    auto f = formas_por_cantidad(lines);
    return ans(std::accumulate(f.begin(), f.end(), 0LL));
}

// formas con el menor número posible de contenedores
Answer part2(const Lines& lines) {
    auto f = formas_por_cantidad(lines);
    return ans(*std::find_if(f.begin(), f.end(), [](long long v) { return v > 0; }));
}

}  // namespace

AOC_REGISTER(2015, 17, part1, part2);
