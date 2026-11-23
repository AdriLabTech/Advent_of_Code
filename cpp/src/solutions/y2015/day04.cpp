// Advent of Code 2015 - Día 4 (el input es la clave secreta: una sola línea de texto)
#include "aoc.hpp"
#include "md5.hpp"

using namespace aoc;

namespace {

// ¿El hash empieza por `ceros` dígitos hexadecimales a cero?
bool empieza_por_ceros(const std::array<std::uint8_t, 16>& hash, int ceros) {
    for (int i = 0; i < ceros; ++i)
        if ((i % 2 == 0 ? hash[i / 2] >> 4 : hash[i / 2] & 0x0f) != 0) return false;
    return true;
}

std::string recortar(const std::string& s) {
    auto a = s.find_first_not_of(" \t\r\n");
    auto b = s.find_last_not_of(" \t\r\n");
    return a == std::string::npos ? "" : s.substr(a, b - a + 1);
}

long long primer_numero(const std::string& clave, int ceros) {
    for (long long n = 1;; ++n)
        if (empieza_por_ceros(md5(clave + std::to_string(n)), ceros)) return n;
}

Answer part1(const Lines& lines) { return ans(primer_numero(recortar(lines.at(0)), 5)); }

Answer part2(const Lines& lines) { return ans(primer_numero(recortar(lines.at(0)), 6)); }

}  // namespace

AOC_REGISTER(2015, 4, part1, part2);
