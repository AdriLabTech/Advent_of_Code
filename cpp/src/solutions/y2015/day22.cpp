// Advent of Code 2015 - Día 22
#include <algorithm>
#include <array>
#include <optional>
#include <queue>
#include <set>
#include <tuple>

#include "aoc.hpp"

using namespace aoc;

namespace {

struct Hechizo { int coste, dano, cura, duracion; };
// el orden es Misil, Drenaje, Escudo, Veneno, Recarga
constexpr Hechizo HECHIZOS[5] = {{53, 4, 0, 0}, {73, 2, 2, 0}, {113, 0, 0, 6}, {173, 0, 0, 6}, {229, 0, 0, 5}};

// Estado del combate: (maná gastado, vida jugador, maná, vida jefe, escudo, veneno, recarga)
using Estado = std::tuple<int, int, int, int, int, int, int>;

struct Resultado { int vida_jefe, mana, armadura, escudo, veneno, recarga; };

// Aplica los efectos activos al comienzo de un turno.
Resultado efectos(int vida_jefe, int mana, int escudo, int veneno, int recarga) {
    return {vida_jefe - (veneno > 0 ? 3 : 0), mana + (recarga > 0 ? 101 : 0), escudo > 0 ? 7 : 0, std::max(0, escudo - 1), std::max(0, veneno - 1), std::max(0, recarga - 1)};
}

// Búsqueda de Dijkstra por maná gastado sobre los estados del combate. nullopt si no se puede ganar.
std::optional<int> minimo_mana(int vida_jefe, int dano_jefe, int vida, int mana, bool dificil) {
    std::priority_queue<Estado, std::vector<Estado>, std::greater<>> cola;
    cola.push({0, vida, mana, vida_jefe, 0, 0, 0});
    std::set<std::array<int, 6>> vistos;
    while (!cola.empty()) {
        auto [gastado, v0, m0, vj0, e0, p0, r0] = cola.top();
        cola.pop();
        if (vj0 <= 0) return gastado;  // estado ganador: se saca por maná creciente, es el mínimo
        if (!vistos.insert({v0, m0, vj0, e0, p0, r0}).second) continue;
        // --- turno del jugador ---
        if (dificil && --v0 <= 0) continue;
        auto ef = efectos(vj0, m0, e0, p0, r0);
        if (ef.vida_jefe <= 0) return gastado;
        for (int h = 0; h < 5; ++h) {
            const auto& hz = HECHIZOS[h];
            if (hz.coste > ef.mana || (h == 2 && ef.escudo > 0) || (h == 3 && ef.veneno > 0) || (h == 4 && ef.recarga > 0)) continue;
            int m = ef.mana - hz.coste, vj = ef.vida_jefe - hz.dano, v = v0 + hz.cura;
            int e = ef.escudo, p = ef.veneno, r = ef.recarga;
            if (h == 2) e = hz.duracion; else if (h == 3) p = hz.duracion; else if (h == 4) r = hz.duracion;
            int total = gastado + hz.coste;
            if (vj <= 0) { cola.push({total, v, m, vj, e, p, r}); continue; }  // gana nada más lanzarlo
            // --- turno del jefe ---
            auto ef2 = efectos(vj, m, e, p, r);
            if (ef2.vida_jefe <= 0) { cola.push({total, v, ef2.mana, ef2.vida_jefe, ef2.escudo, ef2.veneno, ef2.recarga}); continue; }
            v -= std::max(1, dano_jefe - ef2.armadura);
            if (v > 0) cola.push({total, v, ef2.mana, ef2.vida_jefe, ef2.escudo, ef2.veneno, ef2.recarga});
        }
    }
    return std::nullopt;
}

std::vector<long long> leer(const Lines& lines) {
    std::string todo;
    for (const auto& l : lines) todo += l + " ";
    return ints(todo);
}

Answer part1(const Lines& lines) {
    auto n = leer(lines);
    auto r = minimo_mana(int(n[0]), int(n[1]), 50, 500, false);
    return r ? ans(*r) : std::nullopt;
}

Answer part2(const Lines& lines) {
    auto n = leer(lines);
    auto r = minimo_mana(int(n[0]), int(n[1]), 50, 500, true);
    return r ? ans(*r) : std::nullopt;
}

}  // namespace

AOC_REGISTER(2015, 22, part1, part2);
