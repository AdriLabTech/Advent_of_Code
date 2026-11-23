// Advent of Code 2015 - Día 18
#include <algorithm>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int PASOS = 100;
constexpr int PASOS_EJEMPLO_P1 = 4;  // el ejemplo del enunciado (6x6) usa 4 pasos en la parte 1 ...
constexpr int PASOS_EJEMPLO_P2 = 5;  // ... y 5 en la parte 2

using Rejilla = std::vector<std::vector<char>>;

// Una generación del juego de la vida (los vecinos fuera de la rejilla cuentan como apagados).
Rejilla paso(const Rejilla& luces) {
    int lado = static_cast<int>(luces.size());
    Rejilla nuevas(lado, std::vector<char>(lado, 0));
    for (int r = 0; r < lado; ++r)
        for (int c = 0; c < lado; ++c) {
            int vecinos = 0;
            for (int dr = -1; dr <= 1; ++dr)
                for (int dc = -1; dc <= 1; ++dc)
                    if ((dr || dc) && r + dr >= 0 && r + dr < lado && c + dc >= 0 && c + dc < lado) vecinos += luces[r + dr][c + dc];
            nuevas[r][c] = vecinos == 3 || (vecinos == 2 && luces[r][c]);
        }
    return nuevas;
}

long long animar(const Lines& lines, bool esquinas_fijas) {
    Rejilla luces;
    for (const auto& l : lines) {
        if (l.find_first_not_of(" \t\r") == std::string::npos) continue;
        std::vector<char> fila;
        for (char ch : l)
            if (ch == '#' || ch == '.') fila.push_back(ch == '#');
        luces.push_back(fila);
    }
    int lado = static_cast<int>(luces.size());
    int pasos = lado <= 6 ? (esquinas_fijas ? PASOS_EJEMPLO_P2 : PASOS_EJEMPLO_P1) : PASOS;
    auto fijar = [&] {
        if (esquinas_fijas) luces[0][0] = luces[0][lado - 1] = luces[lado - 1][0] = luces[lado - 1][lado - 1] = 1;  // esquinas atascadas encendidas
    };
    fijar();
    for (int i = 0; i < pasos; ++i) {
        luces = paso(luces);
        fijar();
    }
    long long encendidas = 0;
    for (const auto& fila : luces) encendidas += std::count(fila.begin(), fila.end(), 1);
    return encendidas;
}

Answer part1(const Lines& lines) { return ans(animar(lines, false)); }

Answer part2(const Lines& lines) { return ans(animar(lines, true)); }

}  // namespace

AOC_REGISTER(2015, 18, part1, part2);
