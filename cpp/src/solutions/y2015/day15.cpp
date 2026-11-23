// Advent of Code 2015 - Día 15
#include <algorithm>
#include <array>
#include <functional>
#include <optional>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int CUCHARADAS = 100;

using Propiedades = std::array<long long, 5>;  // capacidad, durabilidad, sabor, textura, calorías

// Prueba todos los repartos de las cucharadas entre los ingredientes y devuelve la mejor puntuación.
long long mejor_galleta(const Lines& lines, std::optional<long long> calorias) {
    std::vector<Propiedades> ing;
    for (const auto& l : lines) {
        auto pos = l.find(':');
        if (pos == std::string::npos) continue;
        auto n = ints(l.substr(pos + 1));
        ing.push_back({n[0], n[1], n[2], n[3], n[4]});
    }
    long long mejor = 0;
    std::function<void(std::size_t, int, Propiedades)> repartir = [&](std::size_t i, int restantes, Propiedades prop) {
        if (i == ing.size() - 1) {  // el último ingrediente se lleva lo que queda
            for (int k = 0; k < 5; ++k) prop[k] += restantes * ing[i][k];
            if (!calorias || *calorias == prop[4]) {
                long long puntuacion = 1;
                for (int k = 0; k < 4; ++k) puntuacion *= std::max(prop[k], 0LL);  // un total negativo cuenta como 0
                mejor = std::max(mejor, puntuacion);
            }
            return;
        }
        for (int cantidad = 0; cantidad <= restantes; ++cantidad) {
            Propiedades nuevas = prop;
            for (int k = 0; k < 5; ++k) nuevas[k] += cantidad * ing[i][k];
            repartir(i + 1, restantes - cantidad, nuevas);
        }
    };
    repartir(0, CUCHARADAS, Propiedades{});
    return mejor;
}

Answer part1(const Lines& lines) { return ans(mejor_galleta(lines, std::nullopt)); }

Answer part2(const Lines& lines) { return ans(mejor_galleta(lines, 500)); }

}  // namespace

AOC_REGISTER(2015, 15, part1, part2);
