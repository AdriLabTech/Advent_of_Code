// Advent of Code 2015 - Día 2
#include <algorithm>
#include <array>
#include <cstdio>

#include "aoc.hpp"

using namespace aoc;

namespace {

// Cada línea 'AxBxC' como {a, b, c} con a <= b <= c.
std::vector<std::array<long long, 3>> cajas(const Lines& lines) {
    std::vector<std::array<long long, 3>> out;
    for (const auto& line : lines) {
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        std::array<long long, 3> d{};
        std::sscanf(line.c_str(), "%lldx%lldx%lld", &d[0], &d[1], &d[2]);
        std::sort(d.begin(), d.end());
        out.push_back(d);
    }
    return out;
}

// superficie total + el lado más pequeño (a*b) como holgura
Answer part1(const Lines& lines) {
    long long total = 0;
    for (auto [a, b, c] : cajas(lines)) total += 2 * (a * b + b * c + a * c) + a * b;
    return ans(total);
}

// perímetro de la cara más pequeña + volumen
Answer part2(const Lines& lines) {
    long long total = 0;
    for (auto [a, b, c] : cajas(lines)) total += 2 * (a + b) + a * b * c;
    return ans(total);
}

}  // namespace

AOC_REGISTER(2015, 2, part1, part2);
