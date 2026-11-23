// Advent of Code 2015 - Día 23
#include <sstream>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

// Ejecuta el programa hasta salirse de él y devuelve los registros (a, b).
std::pair<long long, long long> ejecutar(const Lines& lines, long long a) {
    std::vector<std::vector<std::string>> programa;
    for (auto l : lines) {
        if (l.find_first_not_of(" \t\r") == std::string::npos) continue;
        for (auto& c : l)
            if (c == ',') c = ' ';
        std::stringstream ss(l);
        std::vector<std::string> p;
        for (std::string t; ss >> t;) p.push_back(t);
        programa.push_back(p);
    }
    long long registros[2] = {a, 0};
    auto reg = [](const std::string& r) { return r == "b" ? 1 : 0; };
    long long pc = 0;
    while (pc >= 0 && pc < static_cast<long long>(programa.size())) {
        const auto& i = programa[pc];
        long long salto = 1;
        if (i[0] == "hlf") registros[reg(i[1])] /= 2;
        else if (i[0] == "tpl") registros[reg(i[1])] *= 3;
        else if (i[0] == "inc") ++registros[reg(i[1])];
        else if (i[0] == "jmp") salto = std::stoll(i[1]);
        else if (i[0] == "jie" && registros[reg(i[1])] % 2 == 0) salto = std::stoll(i[2]);
        else if (i[0] == "jio" && registros[reg(i[1])] == 1) salto = std::stoll(i[2]);
        pc += salto;
    }
    return {registros[0], registros[1]};
}

// el ejemplo del enunciado (4 instrucciones) deja el resultado en a
Answer part1(const Lines& lines) {
    auto [a, b] = ejecutar(lines, 0);
    long long instrucciones = 0;
    for (const auto& l : lines) instrucciones += l.find_first_not_of(" \t\r") != std::string::npos;
    return ans(instrucciones > 4 ? b : a);
}

Answer part2(const Lines& lines) { return ans(ejecutar(lines, 1).second); }

}  // namespace

AOC_REGISTER(2015, 23, part1, part2);
