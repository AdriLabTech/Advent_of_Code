// Advent of Code 2025 - Día 11
#include <map>
#include <sstream>
#include <unordered_map>

#include "aoc.hpp"

using namespace aoc;

namespace {

const std::vector<std::string> OBLIGATORIOS = {"dac", "fft"};

using Grafo = std::unordered_map<std::string, std::vector<std::string>>;

Grafo leer(const Lines& lines) {
    Grafo grafo;
    for (const auto& l : lines) {
        if (l.find_first_not_of(" \t\r") == std::string::npos) continue;
        auto dos_puntos = l.find(':');
        std::string nombre = l.substr(0, dos_puntos);
        nombre.erase(nombre.find_last_not_of(" \t") + 1);
        std::vector<std::string> salidas;
        if (dos_puntos != std::string::npos) {
            std::stringstream ss(l.substr(dos_puntos + 1));
            for (std::string s; ss >> s;) salidas.push_back(s);
        }
        grafo[nombre] = salidas;
    }
    return grafo;
}

long long caminos(const std::string& nodo, const Grafo& grafo, std::unordered_map<std::string, long long>& memo) {
    if (nodo == "out") return 1;
    if (auto it = memo.find(nodo); it != memo.end()) return it->second;
    long long total = 0;
    if (auto it = grafo.find(nodo); it != grafo.end())
        for (const auto& s : it->second) total += caminos(s, grafo, memo);
    return memo[nodo] = total;
}

// pendientes es una máscara de bits con los obligatorios que aún no se han visitado
long long caminos_obligatorios(const std::string& nodo, unsigned pendientes, const Grafo& grafo,
                               std::map<std::pair<std::string, unsigned>, long long>& memo) {
    if (nodo == "out") return pendientes == 0;  // solo vale si pasó por todos los obligatorios
    if (auto it = memo.find({nodo, pendientes}); it != memo.end()) return it->second;
    unsigned ahora = pendientes;
    for (std::size_t i = 0; i < OBLIGATORIOS.size(); ++i)
        if (OBLIGATORIOS[i] == nodo) ahora &= ~(1u << i);
    long long total = 0;
    if (auto it = grafo.find(nodo); it != grafo.end())
        for (const auto& s : it->second) total += caminos_obligatorios(s, ahora, grafo, memo);
    return memo[{nodo, pendientes}] = total;
}

Answer part1(const Lines& lines) {
    std::unordered_map<std::string, long long> memo;
    return ans(caminos("you", leer(lines), memo));
}

Answer part2(const Lines& lines) {
    std::map<std::pair<std::string, unsigned>, long long> memo;
    return ans(caminos_obligatorios("svr", (1u << OBLIGATORIOS.size()) - 1, leer(lines), memo));
}

}  // namespace

AOC_REGISTER(2025, 11, part1, part2);
