// Núcleo de Advent of Code en C++: registro de días, lectura de input y helpers.
// Sin clases ni herencia: cada día son dos funciones libres y una línea AOC_REGISTER.
#pragma once

#include <fstream>
#include <functional>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace aoc {

using Lines = std::vector<std::string>;
using Answer = std::optional<std::string>;  // std::nullopt = parte pendiente
using Solver = Answer (*)(const Lines&);

struct Day {
    int year;
    int day;
    Solver part1;
    Solver part2;
};

inline std::vector<Day>& registry() {
    static std::vector<Day> days;  // se rellena antes de main() con AOC_REGISTER
    return days;
}

inline bool register_day(int year, int day, Solver p1, Solver p2) {
    registry().push_back({year, day, p1, p2});
    return true;
}

// --- helpers para los días ---

/// Convierte cualquier valor imprimible en Answer: return ans(total);
template <typename T>
Answer ans(const T& value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

/// Versión para enteros de 128 bits (ostream no sabe imprimirlos): return ans(valor);
inline Answer ans(unsigned __int128 value) {
    std::string out = value == 0 ? "0" : "";
    for (; value > 0; value /= 10) out.insert(out.begin(), static_cast<char>('0' + static_cast<int>(value % 10)));
    return out;
}

/// Todos los enteros (con signo) que aparecen en un texto.
inline std::vector<long long> ints(const std::string& text) {
    static const std::regex re(R"(-?\d+)");
    std::vector<long long> out;
    for (std::sregex_iterator it(text.begin(), text.end(), re), end; it != end; ++it) out.push_back(std::stoll(it->str()));
    return out;
}

/// Divide las líneas en bloques separados por líneas en blanco.
inline std::vector<Lines> paragraphs(const Lines& lines) {
    std::vector<Lines> blocks;
    Lines cur;
    for (const auto& l : lines) {
        if (l.find_first_not_of(" \t\r") == std::string::npos) {
            if (!cur.empty()) { blocks.push_back(cur); cur.clear(); }
        } else {
            cur.push_back(l);
        }
    }
    if (!cur.empty()) blocks.push_back(cur);
    return blocks;
}

}  // namespace aoc

#define AOC_CONCAT_(a, b) a##b
#define AOC_CONCAT(a, b) AOC_CONCAT_(a, b)
/// Registra un día: AOC_REGISTER(2025, 1, part1, part2);
#define AOC_REGISTER(year, day, p1, p2) \
    static const bool AOC_CONCAT(aoc_registered_, __LINE__) = ::aoc::register_day(year, day, p1, p2)
