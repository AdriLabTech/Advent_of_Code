// Advent of Code 2025 - Día 5
#include <algorithm>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Rango = std::pair<long long, long long>;

// Rangos frescos 'a-b', línea en blanco y luego los IDs disponibles.
std::pair<std::vector<Rango>, std::vector<long long>> leer(const Lines& lines) {
    std::vector<Rango> rangos;
    std::vector<long long> ids;
    bool en_rangos = true;
    for (const auto& line : lines) {
        if (line.find_first_not_of(" \t\r") == std::string::npos) {
            en_rangos = false;
        } else if (en_rangos) {
            auto guion = line.find('-');
            rangos.push_back({std::stoll(line.substr(0, guion)), std::stoll(line.substr(guion + 1))});
        } else {
            ids.push_back(std::stoll(line));
        }
    }
    return {rangos, ids};
}

Answer part1(const Lines& lines) {
    auto [rangos, ids] = leer(lines);
    long long frescos = 0;
    for (long long id : ids)
        frescos += std::any_of(rangos.begin(), rangos.end(), [id](const Rango& r) { return r.first <= id && id <= r.second; });
    return ans(frescos);
}

Answer part2(const Lines& lines) {
    // unión de rangos: se ordenan y se fusionan los que se solapan o se tocan; luego se suman sus longitudes
    auto rangos = leer(lines).first;
    std::sort(rangos.begin(), rangos.end());
    long long total = 0, hasta = -1;
    for (auto [a, b] : rangos)
        if (b > hasta) {
            total += b - std::max(a, hasta + 1) + 1;
            hasta = b;
        }
    return ans(total);
}

}  // namespace

AOC_REGISTER(2025, 5, part1, part2);
