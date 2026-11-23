// Advent of Code 2015 - Día 5
#include <algorithm>

#include "aoc.hpp"

using namespace aoc;

namespace {

bool es_buena_v1(const std::string& s) {
    auto vocales = std::count_if(s.begin(), s.end(), [](char c) { return std::string("aeiou").find(c) != std::string::npos; });
    bool doble = false;
    for (std::size_t i = 1; i < s.size(); ++i) doble |= s[i] == s[i - 1];
    bool prohibida = false;
    for (const char* p : {"ab", "cd", "pq", "xy"}) prohibida |= s.find(p) != std::string::npos;
    return vocales >= 3 && doble && !prohibida;
}

bool es_buena_v2(const std::string& s) {
    // un par de letras que reaparece más adelante sin solaparse
    bool par_repetido = false;
    for (std::size_t i = 0; i + 1 < s.size() && !par_repetido; ++i) par_repetido = s.find(s.substr(i, 2), i + 2) != std::string::npos;
    // una letra que se repite con otra en medio (xyx)
    bool letra_entre = false;
    for (std::size_t i = 0; i + 2 < s.size(); ++i) letra_entre |= s[i] == s[i + 2];
    return par_repetido && letra_entre;
}

Answer part1(const Lines& lines) { return ans(std::count_if(lines.begin(), lines.end(), es_buena_v1)); }

Answer part2(const Lines& lines) { return ans(std::count_if(lines.begin(), lines.end(), es_buena_v2)); }

}  // namespace

AOC_REGISTER(2015, 5, part1, part2);
