// Advent of Code 2015 - Día 6
#include <algorithm>
#include <numeric>

#include "aoc.hpp"

using namespace aoc;

namespace {

constexpr int LADO = 1000;

enum class Accion { On, Off, Toggle };

struct Instruccion {
    Accion accion;
    int x1, y1, x2, y2;  // x1<=x2 e y1<=y2
};

std::vector<Instruccion> instrucciones(const Lines& lines) {
    std::vector<Instruccion> out;
    for (const auto& line : lines) {
        if (line.find_first_not_of(" \t\r") == std::string::npos) continue;
        Accion a = line.rfind("turn on", 0) == 0 ? Accion::On : line.rfind("turn off", 0) == 0 ? Accion::Off : Accion::Toggle;
        auto n = ints(line);
        out.push_back({a, int(std::min(n[0], n[2])), int(std::min(n[1], n[3])), int(std::max(n[0], n[2])), int(std::max(n[1], n[3]))});
    }
    return out;
}

Answer part1(const Lines& lines) {
    std::vector<char> luces(LADO * LADO, 0);
    for (const auto& i : instrucciones(lines))
        for (int y = i.y1; y <= i.y2; ++y)
            for (int x = i.x1; x <= i.x2; ++x) {
                char& l = luces[y * LADO + x];
                l = i.accion == Accion::On ? 1 : i.accion == Accion::Off ? 0 : !l;
            }
    return ans(std::count(luces.begin(), luces.end(), 1));
}

Answer part2(const Lines& lines) {
    std::vector<int> brillo(LADO * LADO, 0);
    for (const auto& i : instrucciones(lines))
        for (int y = i.y1; y <= i.y2; ++y)
            for (int x = i.x1; x <= i.x2; ++x) {
                int& b = brillo[y * LADO + x];
                b = i.accion == Accion::On ? b + 1 : i.accion == Accion::Off ? std::max(0, b - 1) : b + 2;
            }
    return ans(std::accumulate(brillo.begin(), brillo.end(), 0LL));
}

}  // namespace

AOC_REGISTER(2015, 6, part1, part2);
