// Advent of Code 2015 - Día 16
#include <map>
#include <sstream>

#include "aoc.hpp"

using namespace aoc;

namespace {

const std::map<std::string, int> HUELLA = {{"children", 3}, {"cats", 7},     {"samoyeds", 2}, {"pomeranians", 3}, {"akitas", 0},
                                           {"vizslas", 0},   {"goldfish", 5}, {"trees", 3},    {"cars", 2},        {"perfumes", 1}};

// La tía cuyos recuerdos cumplen `orden(compuesto)` (el signo que debe tener su valor menos la huella).
template <typename F>
Answer buscar(const Lines& lines, F orden) {
    for (const auto& l : lines) {
        auto dos_puntos = l.find(':');
        if (dos_puntos == std::string::npos) continue;
        std::stringstream ss(l.substr(dos_puntos + 1));
        bool cumple = true;
        for (std::string trozo; std::getline(ss, trozo, ',');) {
            std::stringstream par(trozo);
            std::string nombre;
            int cantidad;
            std::getline(par, nombre, ':');
            par >> cantidad;
            nombre.erase(0, nombre.find_first_not_of(' '));
            int ref = HUELLA.at(nombre);
            cumple &= (cantidad > ref ? 1 : cantidad < ref ? -1 : 0) == orden(nombre);
        }
        if (cumple) return ans(std::stoi(l.substr(4, dos_puntos - 4)));
    }
    return std::nullopt;
}

Answer part1(const Lines& lines) {
    return buscar(lines, [](const std::string&) { return 0; });
}

// cats y trees: mayor que la huella; pomeranians y goldfish: menor
Answer part2(const Lines& lines) {
    return buscar(lines, [](const std::string& k) { return k == "cats" || k == "trees" ? 1 : k == "pomeranians" || k == "goldfish" ? -1 : 0; });
}

}  // namespace

AOC_REGISTER(2015, 16, part1, part2);
