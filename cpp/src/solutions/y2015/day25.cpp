// Advent of Code 2015 - Día 25 (el input es 'Enter the code at row R, column C.')
#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr long long PRIMER_CODIGO = 20151125, MULTIPLICADOR = 252533, MODULO = 33554393;

// Código de la casilla (fila, columna): el papel se rellena por diagonales, así que primero se halla el
// número de orden n de la casilla y luego se aplica n-1 veces el generador (con potencia modular, sin bucle).
long long codigo(long long fila, long long columna) {
    long long diagonal = fila + columna - 1;  // las diagonales anteriores contienen 1 + 2 + ... + (diagonal-1) casillas
    long long n = (diagonal - 1) * diagonal / 2 + columna;
    long long base = MULTIPLICADOR, exponente = n - 1, resultado = 1;
    for (; exponente > 0; exponente >>= 1, base = base * base % MODULO)
        if (exponente & 1) resultado = resultado * base % MODULO;
    return PRIMER_CODIGO * resultado % MODULO;
}

Answer part1(const Lines& lines) {
    auto n = ints(lines.at(0));
    return ans(codigo(n[0], n[1]));
}

Answer part2(const Lines&) {
    return std::nullopt;  // la parte 2 es la estrella final gratuita (no tiene puzzle)
}

}  // namespace

AOC_REGISTER(2015, 25, part1, part2);
