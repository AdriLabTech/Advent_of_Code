// Advent of Code 2015 - Día 19
#include <algorithm>
#include <cctype>
#include <set>
#include <utility>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Reemplazos = std::vector<std::pair<std::string, std::string>>;

// Reemplazos 'X => Y', una línea en blanco y la molécula.
std::pair<Reemplazos, std::string> leer(const Lines& lines) {
    Reemplazos reemplazos;
    std::string molecula;
    for (auto l : lines) {
        l.erase(l.find_last_not_of(" \t\r") + 1);
        auto flecha = l.find(" => ");
        if (flecha != std::string::npos) reemplazos.push_back({l.substr(0, flecha), l.substr(flecha + 4)});
        else if (!l.empty()) molecula = l;
    }
    return {reemplazos, molecula};
}

std::vector<std::size_t> apariciones(const std::string& texto, const std::string& trozo) {
    std::vector<std::size_t> out;
    for (auto i = texto.find(trozo); i != std::string::npos; i = texto.find(trozo, i + 1)) out.push_back(i);
    return out;
}

Answer part1(const Lines& lines) {
    auto [reemplazos, molecula] = leer(lines);
    std::set<std::string> resultados;
    for (const auto& [origen, destino] : reemplazos)
        for (auto i : apariciones(molecula, origen))  // cada aparición del origen es un reemplazo posible
            resultados.insert(molecula.substr(0, i) + destino + molecula.substr(i + origen.size()));
    return ans(resultados.size());
}

// Pasos mínimos de 'e' a la molécula: búsqueda en anchura hacia atrás (de la molécula a 'e'). Solo sirve para moléculas cortas.
int pasos_busqueda(const Reemplazos& reemplazos, const std::string& molecula) {
    std::set<std::string> actual{molecula};
    int pasos = 0;
    while (!actual.count("e")) {
        ++pasos;
        std::set<std::string> siguiente;
        for (const auto& m : actual)
            for (const auto& [origen, destino] : reemplazos)
                for (auto i : apariciones(m, destino)) {
                    std::string nueva = m.substr(0, i) + origen + m.substr(i + destino.size());
                    if (origen != "e" || nueva == "e") siguiente.insert(nueva);  // 'e' solo vale como paso final
                }
        actual = siguiente;
    }
    return pasos;
}

Answer part2(const Lines& lines) {
    auto [reemplazos, molecula] = leer(lines);
    if (molecula.find("Rn") == std::string::npos) return ans(pasos_busqueda(reemplazos, molecula));
    // Molécula real: cada reemplazo suma un elemento, salvo los de la forma X => X Rn ... Ar (que añaden Rn y Ar)
    // y los que llevan Y (cada Y añade además una coma y otro elemento). Por eso los pasos son:
    // elementos - (Rn + Ar) - 2 * Y - 1
    long long elementos = std::count_if(molecula.begin(), molecula.end(), [](unsigned char c) { return std::isupper(c); });
    long long rn = apariciones(molecula, "Rn").size(), ar = apariciones(molecula, "Ar").size(), y = apariciones(molecula, "Y").size();
    return ans(elementos - rn - ar - 2 * y - 1);
}

}  // namespace

AOC_REGISTER(2015, 19, part1, part2);
