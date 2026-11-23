// Advent of Code 2015 - Día 1
#include "aoc.hpp"

using namespace aoc;

namespace {

int paso(int piso, char c) { return c == '(' ? piso + 1 : c == ')' ? piso - 1 : piso; }

Answer part1(const Lines& lines) {
    int piso = 0;
    for (char c : lines.at(0)) piso = paso(piso, c);
    return ans(piso);
}

// Posición (empezando en 1) del primer carácter que lleva al piso -1.
Answer part2(const Lines& lines) {
    int piso = 0;
    const std::string& s = lines.at(0);
    for (std::size_t i = 0; i < s.size(); ++i) {
        piso = paso(piso, s[i]);
        if (piso == -1) return ans(i + 1);
    }
    return std::nullopt;  // nunca entra en el sótano
}

}  // namespace

AOC_REGISTER(2015, 1, part1, part2);
