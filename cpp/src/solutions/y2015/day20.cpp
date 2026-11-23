// Advent of Code 2015 - Día 20 (el input es un número en una línea)
#include <algorithm>

#include "aoc.hpp"

using namespace aoc;

namespace {

// regalos[c] = presentes que recibe la casa c (criba: cada elfo recorre sus casas) hasta la casa `limite`.
std::vector<long long> regalos(long long limite, int por_elfo, int casas_por_elfo) {  // casas_por_elfo 0 = sin límite
    std::vector<long long> casas(limite + 1, 0);
    for (long long elfo = 1; elfo <= limite; ++elfo) {
        long long ultima = casas_por_elfo ? std::min(limite, elfo * casas_por_elfo) : limite;
        for (long long casa = elfo; casa <= ultima; casa += elfo) casas[casa] += por_elfo * elfo;
    }
    return casas;
}

long long primera_casa(long long objetivo, int por_elfo, int casas_por_elfo) {
    for (long long limite = 1 << 14;; limite *= 2) {  // si no aparece, se duplica el rango y se vuelve a cribar
        auto casas = regalos(limite, por_elfo, casas_por_elfo);
        auto it = std::find_if(casas.begin(), casas.end(), [objetivo](long long t) { return t >= objetivo; });
        if (it != casas.end()) return it - casas.begin();
    }
}

Answer part1(const Lines& lines) { return ans(primera_casa(std::stoll(lines.at(0)), 10, 0)); }

// cada elfo reparte 11 veces su número y solo a 50 casas
Answer part2(const Lines& lines) { return ans(primera_casa(std::stoll(lines.at(0)), 11, 50)); }

}  // namespace

AOC_REGISTER(2015, 20, part1, part2);
