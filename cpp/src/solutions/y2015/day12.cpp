// Advent of Code 2015 - Día 12
#include <cctype>
#include <numeric>

#include "aoc.hpp"

using namespace aoc;

namespace {

// Suma de todos los números ignorando los objetos {...} que tengan algún valor "red" (los arrays no cuentan como objeto).
// Se recorre el texto con una pila: cada { o [ abre un nivel con su suma; al cerrarlo se suma al nivel de fuera
// (salvo un objeto con "red", que aporta 0).
long long suma_sin_rojos(const std::string& t) {
    struct Nivel { long long suma; bool es_objeto, tiene_rojo; };
    std::vector<Nivel> pila{{0, false, false}};
    for (std::size_t i = 0; i < t.size(); ++i) {
        char c = t[i];
        if (c == '{' || c == '[') {
            pila.push_back({0, c == '{', false});
        } else if (c == '}' || c == ']') {
            Nivel n = pila.back();
            pila.pop_back();
            pila.back().suma += n.tiene_rojo ? 0 : n.suma;
        } else if (c == '"') {
            auto fin = t.find('"', i + 1);
            bool es_clave = fin + 1 < t.size() && t[fin + 1] == ':';  // un ':' detrás significa que era una clave, no un valor
            if (t.compare(i + 1, fin - i - 1, "red") == 0 && pila.back().es_objeto && !es_clave) pila.back().tiene_rojo = true;
            i = fin;
        } else if (c == '-' || std::isdigit(static_cast<unsigned char>(c))) {
            std::size_t fin = i + 1;
            while (fin < t.size() && std::isdigit(static_cast<unsigned char>(t[fin]))) ++fin;
            pila.back().suma += std::stoll(t.substr(i, fin - i));
            i = fin - 1;
        }
    }
    return pila[0].suma;
}

Answer part1(const Lines& lines) {
    auto n = ints(lines.at(0));
    return ans(std::accumulate(n.begin(), n.end(), 0LL));
}

Answer part2(const Lines& lines) { return ans(suma_sin_rojos(lines.at(0))); }

}  // namespace

AOC_REGISTER(2015, 12, part1, part2);
