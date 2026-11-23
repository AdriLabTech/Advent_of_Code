// Advent of Code 2025 - Día 12
#include <algorithm>
#include <map>
#include <set>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Celda = std::pair<int, int>;
using Forma = std::vector<Celda>;

struct Region {
    int ancho, alto;
    std::vector<int> cantidades;
};

// Formas ('0:' + filas) y regiones ('AxB: q0 q1 ...').
void leer(const Lines& lines, std::map<int, Forma>& formas, std::vector<Region>& regiones) {
    for (const auto& bloque : paragraphs(lines)) {
        if (bloque[0].back() == ':') {
            Forma celdas;
            for (std::size_t r = 1; r < bloque.size(); ++r)
                for (std::size_t c = 0; c < bloque[r].size(); ++c)
                    if (bloque[r][c] == '#') celdas.push_back({int(r - 1), int(c)});
            formas[std::stoi(bloque[0])] = celdas;
        } else {
            for (const auto& linea : bloque) {
                auto n = ints(linea);  // ancho, alto, q0 ... q5
                Region reg{int(n[0]), int(n[1]), {}};
                for (std::size_t i = 2; i < n.size(); ++i) reg.cantidades.push_back(int(n[i]));
                regiones.push_back(reg);
            }
        }
    }
}

// Las rotaciones y reflejos distintos de una forma, normalizados a la esquina superior izquierda.
std::vector<Forma> orientaciones(const Forma& forma) {
    std::set<Forma> resultado;
    Forma celdas = forma;
    for (int giro = 0; giro < 4; ++giro) {
        for (auto& [r, c] : celdas) std::tie(r, c) = std::pair{c, -r};  // rotar 90°
        for (int espejo = 0; espejo < 2; ++espejo) {
            Forma f = celdas;
            if (espejo) for (auto& p : f) p.second = -p.second;
            int menor_r = f[0].first, menor_c = f[0].second;
            for (auto& p : f) { menor_r = std::min(menor_r, p.first); menor_c = std::min(menor_c, p.second); }
            for (auto& p : f) { p.first -= menor_r; p.second -= menor_c; }
            std::sort(f.begin(), f.end());
            resultado.insert(f);
        }
    }
    return {resultado.begin(), resultado.end()};
}

struct Tablero {
    int ancho, alto;
    std::vector<char> libres;
    std::vector<int> restantes;
    const std::map<int, std::vector<Forma>>& orient;

    // Rellena la primera celda libre (por filas) con una pieza o la deja vacía (si queda holgura).
    bool resolver(int pos, int hueco) {
        while (pos < ancho * alto && !libres[pos]) ++pos;
        if (pos == ancho * alto) return std::all_of(restantes.begin(), restantes.end(), [](int q) { return q == 0; });
        int r0 = pos / ancho, c0 = pos % ancho;
        for (std::size_t i = 0; i < restantes.size(); ++i) {
            if (restantes[i] == 0) continue;
            for (const auto& forma : orient.at(static_cast<int>(i))) {
                // la primera celda de la forma (por filas) es la que se apoya en la celda libre
                auto [dr, dc] = forma[0];
                std::vector<int> destino;
                bool cabe = true;
                for (auto [r, c] : forma) {
                    int rr = r0 + r - dr, cc = c0 + c - dc;
                    if (rr < 0 || cc < 0 || rr >= alto || cc >= ancho || !libres[rr * ancho + cc]) { cabe = false; break; }
                    destino.push_back(rr * ancho + cc);
                }
                if (!cabe) continue;
                for (int d : destino) libres[d] = 0;
                --restantes[i];
                if (resolver(pos + 1, hueco)) return true;
                ++restantes[i];
                for (int d : destino) libres[d] = 1;
            }
        }
        if (hueco > 0) {
            libres[pos] = 0;  // dejar esta celda vacía
            if (resolver(pos + 1, hueco - 1)) return true;
            libres[pos] = 1;
        }
        return false;
    }
};

Answer part1(const Lines& lines) {
    std::map<int, Forma> formas;
    std::vector<Region> regiones;
    leer(lines, formas, regiones);
    std::map<int, std::vector<Forma>> orient;
    for (auto& [i, f] : formas) orient[i] = orientaciones(f);

    int total = 0;
    for (const auto& reg : regiones) {
        int piezas = 0, celdas = 0;
        for (std::size_t i = 0; i < reg.cantidades.size(); ++i) {
            piezas += reg.cantidades[i];
            celdas += reg.cantidades[i] * static_cast<int>(formas[static_cast<int>(i)].size());
        }
        if (celdas > reg.ancho * reg.alto) continue;                          // no caben ni sin huecos
        if (piezas <= (reg.ancho / 3) * (reg.alto / 3)) { ++total; continue; }  // cada pieza cabe en un cuadrado de 3x3
        Tablero t{reg.ancho, reg.alto, std::vector<char>(reg.ancho * reg.alto, 1), reg.cantidades, orient};
        total += t.resolver(0, reg.ancho * reg.alto - celdas);
    }
    return ans(total);
}

Answer part2(const Lines&) {
    return std::nullopt;  // pendiente: la parte 2 se desbloquea al completar el resto de días
}

}  // namespace

AOC_REGISTER(2025, 12, part1, part2);
