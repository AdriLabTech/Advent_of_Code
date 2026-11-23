// Advent of Code 2025 - Día 1
#include <cstdlib>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int DIAL = 100;  // posiciones del dial (0..99)
constexpr int START = 50;  // posición inicial

// Cada línea (L68, R48...) como desplazamiento con signo: L = negativo, R = positivo.
std::vector<int> rotations(const Lines& lines) {
    std::vector<int> out;
    for (const auto& line : lines) {
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        int n = std::stoi(line.substr(1));
        out.push_back(line[0] == 'L' ? -n : n);
    }
    return out;
}

// El % de C++ puede dar negativos: se normaliza al rango 0..99.
int mod(int value) { return ((value % DIAL) + DIAL) % DIAL; }

Answer part1(const Lines& lines) {
    int pos = START, zeros = 0;
    for (int delta : rotations(lines)) {
        pos = mod(pos + delta);
        if (pos == 0) ++zeros;
    }
    return ans(zeros);
}

Answer part2(const Lines& lines) {
    int pos = START;
    long long zeros = 0;
    for (int delta : rotations(lines)) {
        // Girar a la izquierda equivale a girar a la derecha desde la posición "espejo" (DIAL - pos).
        // Así solo hay que contar cuántas veces se cruza un múltiplo de 100 hacia delante.
        int start = delta > 0 ? pos : mod(DIAL - pos);
        zeros += (start + std::abs(delta)) / DIAL;
        pos = mod(pos + delta);
    }
    return ans(zeros);
}

}  // namespace

AOC_REGISTER(2025, 1, part1, part2);
