// Advent of Code 2015 - Día 11
#include <algorithm>
#include <set>

#include "aoc.hpp"

using namespace aoc;

namespace {

const std::string PROHIBIDAS = "iol";

// Suma uno como si fuera un número en base 26 (z pasa a a y acarrea). Salta de golpe las que tienen i, o o l.
void incrementar(std::string& clave) {
    auto i = clave.find_first_of(PROHIBIDAS);
    if (i != std::string::npos) {  // si ya hay una letra prohibida, todo lo que va detrás se pone a 'a'
        ++clave[i];
        std::fill(clave.begin() + i + 1, clave.end(), 'a');
        return;
    }
    for (int k = static_cast<int>(clave.size()) - 1; k >= 0; --k) {
        if (clave[k] == 'z') clave[k] = 'a';
        else { ++clave[k]; break; }
    }
}

bool es_valida(const std::string& c) {
    bool escalera = false;
    for (std::size_t i = 0; i + 2 < c.size(); ++i) escalera |= c[i] + 1 == c[i + 1] && c[i + 1] + 1 == c[i + 2];
    bool sin_prohibidas = c.find_first_of(PROHIBIDAS) == std::string::npos;
    std::set<char> dobles;  // letras distintas dobles
    for (std::size_t i = 0; i + 1 < c.size(); ++i)
        if (c[i] == c[i + 1]) dobles.insert(c[i]);
    return escalera && sin_prohibidas && dobles.size() >= 2;
}

std::string siguiente_clave(std::string clave) {
    do incrementar(clave); while (!es_valida(clave));
    return clave;
}

std::string primera(const Lines& lines) {
    std::string s = lines.at(0);
    s.erase(s.find_last_not_of(" \t\r") + 1);
    return s;
}

Answer part1(const Lines& lines) { return siguiente_clave(primera(lines)); }

Answer part2(const Lines& lines) { return siguiente_clave(siguiente_clave(primera(lines))); }

}  // namespace

AOC_REGISTER(2015, 11, part1, part2);
