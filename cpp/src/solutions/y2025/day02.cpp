// Advent of Code 2025 - Día 2
#include <algorithm>
#include <sstream>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Entero = __int128;  // los productos intermedios pueden superar los 64 bits

// Líneas 'a-b,c-d,...' como lista de (a, b).
std::vector<std::pair<Entero, Entero>> rangos(const Lines& lines) {
    std::vector<std::pair<Entero, Entero>> out;
    for (const auto& line : lines) {
        std::stringstream ss(line);
        for (std::string r; std::getline(ss, r, ',');) {
            auto guion = r.find('-');
            if (guion != std::string::npos) out.push_back({std::stoull(r.substr(0, guion)), std::stoull(r.substr(guion + 1))});
        }
    }
    return out;
}

int digitos(Entero n) {
    int d = 0;
    for (; n > 0; n /= 10) ++d;
    return d;
}

Entero diez(int potencia) {
    Entero v = 1;
    for (int i = 0; i < potencia; ++i) v *= 10;
    return v;
}

// Suma de los números de `largo` dígitos en [a, b] formados repitiendo un bloque de `periodo` dígitos.
Entero suma_con_periodo(Entero a, Entero b, int largo, int periodo) {
    a = std::max(a, diez(largo - 1));
    b = std::min(b, diez(largo) - 1);
    Entero m = (diez(largo) - 1) / (diez(periodo) - 1);  // n = x * m con x de `periodo` dígitos
    Entero menor = std::max(diez(periodo - 1), (a + m - 1) / m);
    Entero mayor = std::min(diez(periodo) - 1, b / m);
    return menor <= mayor ? m * (menor + mayor) * (mayor - menor + 1) / 2 : 0;
}

// ID inválido = un bloque repetido exactamente dos veces: periodo = mitad de los dígitos
Answer part1(const Lines& lines) {
    Entero total = 0;
    for (auto [a, b] : rangos(lines))
        for (int largo = 2; largo <= digitos(b); largo += 2) total += suma_con_periodo(a, b, largo, largo / 2);
    return ans(static_cast<unsigned __int128>(total));
}

// ahora vale cualquier número de repeticiones (>= 2): un periodo p < largo que divida al largo.
// Un mismo número puede tener varios periodos (111111 -> 1, 2 y 3), así que se suma por periodo
// mínimo exacto: g[p] = (números con periodo p) - (los que ya tienen un periodo menor que divide a p)
Answer part2(const Lines& lines) {
    Entero total = 0;
    for (auto [a, b] : rangos(lines))
        for (int largo = 2; largo <= digitos(b); ++largo) {
            std::vector<std::pair<int, Entero>> g;
            for (int p = 1; p < largo; ++p) {
                if (largo % p != 0) continue;
                Entero ya_contados = 0;
                for (auto& [d, suma] : g)
                    if (p % d == 0) ya_contados += suma;
                g.push_back({p, suma_con_periodo(a, b, largo, p) - ya_contados});
            }
            for (auto& [p, suma] : g) total += suma;
        }
    return ans(static_cast<unsigned __int128>(total));
}

}  // namespace

AOC_REGISTER(2025, 2, part1, part2);
