// Advent of Code 2025 - Día 3
#include "aoc.hpp"

using namespace aoc;

namespace {

bool vacia(const std::string& s) { return s.find_first_not_of(" \t\r") == std::string::npos; }

// Número más grande que se forma encendiendo `cuantas` baterías sin cambiar su orden (voraz).
long long mayor_joltaje(const std::string& banco, std::size_t cuantas) {
    std::string elegidas;
    for (std::size_t i = 0; i < banco.size(); ++i) {
        // una elegida peor que la actual se descarta mientras queden baterías de sobra para completar el número
        while (!elegidas.empty() && elegidas.back() < banco[i] && elegidas.size() + banco.size() - i > cuantas) elegidas.pop_back();
        if (elegidas.size() < cuantas) elegidas.push_back(banco[i]);
    }
    return std::stoll(elegidas);
}

Answer total(const Lines& lines, std::size_t cuantas) {
    long long suma = 0;
    for (const auto& line : lines) {
        if (vacia(line)) continue;
        std::string banco = line;
        banco.erase(banco.find_last_not_of(" \t\r") + 1);
        suma += mayor_joltaje(banco, cuantas);
    }
    return ans(suma);
}

Answer part1(const Lines& lines) { return total(lines, 2); }

Answer part2(const Lines& lines) { return total(lines, 12); }

}  // namespace

AOC_REGISTER(2025, 3, part1, part2);
