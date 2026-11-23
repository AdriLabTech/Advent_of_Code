// Advent of Code 2015 - Día 24
#include <algorithm>
#include <functional>
#include <numeric>
#include <optional>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Paquetes = std::vector<long long>;

// Recorre los subconjuntos de `paquetes` que suman `peso`; se detiene cuando `f` devuelve false.
void combinaciones(const Paquetes& paquetes, long long peso, const std::function<bool(const Paquetes&)>& f) {
    Paquetes actual;
    std::function<bool(std::size_t, long long)> rec = [&](std::size_t desde, long long resta) {
        if (resta == 0) return f(actual);
        for (std::size_t i = desde; i < paquetes.size(); ++i) {
            if (paquetes[i] > resta) continue;
            actual.push_back(paquetes[i]);
            bool seguir = rec(i + 1, resta - paquetes[i]);
            actual.pop_back();
            if (!seguir) return false;
        }
        return true;
    };
    rec(0, peso);
}

Paquetes sin(const Paquetes& paquetes, const Paquetes& grupo) {
    Paquetes resto;
    for (auto p : paquetes)
        if (std::find(grupo.begin(), grupo.end(), p) == grupo.end()) resto.push_back(p);
    return resto;
}

// ¿Se pueden repartir los paquetes en `grupos` grupos de `peso` cada uno?
bool se_puede_repartir(const Paquetes& paquetes, int grupos, long long peso) {
    if (grupos == 1) return std::accumulate(paquetes.begin(), paquetes.end(), 0LL) == peso;
    bool hallado = false;
    combinaciones(paquetes, peso, [&](const Paquetes& grupo) {
        hallado = se_puede_repartir(sin(paquetes, grupo), grupos - 1, peso);
        return !hallado;  // seguir buscando mientras no se haya hallado
    });
    return hallado;
}

std::optional<long long> mejor_entrelazamiento(const Lines& lines, int grupos) {
    Paquetes paquetes;
    for (const auto& l : lines)
        if (l.find_first_not_of(" \t\r") != std::string::npos) paquetes.push_back(std::stoll(l));
    long long peso = std::accumulate(paquetes.begin(), paquetes.end(), 0LL) / grupos;
    // se buscan todos los primeros grupos que suman el peso; interesa el de menos paquetes y, a igualdad, el de menor producto
    std::optional<std::pair<std::size_t, long long>> mejor;
    combinaciones(paquetes, peso, [&](const Paquetes& grupo) {
        std::pair<std::size_t, long long> clave{grupo.size(), std::accumulate(grupo.begin(), grupo.end(), 1LL, std::multiplies<>())};
        if ((!mejor || clave < *mejor) && se_puede_repartir(sin(paquetes, grupo), grupos - 1, peso)) mejor = clave;
        return true;
    });
    return mejor ? std::optional<long long>(mejor->second) : std::nullopt;
}

Answer part1(const Lines& lines) {
    auto r = mejor_entrelazamiento(lines, 3);
    return r ? ans(*r) : std::nullopt;
}

Answer part2(const Lines& lines) {
    auto r = mejor_entrelazamiento(lines, 4);
    return r ? ans(*r) : std::nullopt;
}

}  // namespace

AOC_REGISTER(2015, 24, part1, part2);
