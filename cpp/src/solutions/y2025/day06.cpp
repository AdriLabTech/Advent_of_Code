// Advent of Code 2025 - Día 6
#include <algorithm>
#include <cctype>
#include <map>
#include <optional>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Entero = unsigned __int128;  // los productos pueden superar los 64 bits

bool vacia(const std::string& s) { return s.find_first_not_of(" \t\r") == std::string::npos; }

Entero a_entero(const std::string& s) {
    Entero v = 0;
    for (char c : s) v = v * 10 + (c - '0');
    return v;
}

Answer part1(const Lines& lines) {
    // cada columna de la hoja: varios números y, al final, el operador
    std::map<std::size_t, std::vector<std::string>> columnas;
    for (const auto& line : lines) {
        if (vacia(line)) continue;
        std::vector<std::string> tokens;
        if (line.find('*') != std::string::npos) {
            for (char c : line)
                if (c == '*' || c == '+') tokens.push_back(std::string(1, c));
        } else {
            std::string actual;
            for (char c : line + " ") {
                if (std::isdigit(static_cast<unsigned char>(c))) actual += c;
                else if (!actual.empty()) { tokens.push_back(actual); actual.clear(); }
            }
        }
        for (std::size_t i = 0; i < tokens.size(); ++i) columnas[i].push_back(tokens[i]);
    }

    Entero total = 0;
    for (const auto& [_, col] : columnas) {
        Entero valor = a_entero(col[0]);
        for (std::size_t i = 1; i + 1 < col.size(); ++i) {
            if (col.back() == "+") valor += a_entero(col[i]);
            else if (col.back() == "*") valor *= a_entero(col[i]);
        }
        total += valor;
    }
    return ans(total);
}

Answer part2(const Lines& lines) {
    // se lee carácter a carácter: cada columna de la hoja es un número y el operador marca el grupo
    Lines filas;
    for (const auto& l : lines)
        if (!vacia(l)) filas.push_back(l);
    std::size_t ancho = 0;
    for (const auto& f : filas) ancho = std::max(ancho, f.size());

    Entero total = 0;
    std::optional<Entero> acumulado;
    bool en_grupo = false, multiplica = false;
    for (std::size_t i = 0; i < ancho; ++i) {
        std::string columna;
        for (const auto& f : filas)
            if (i < f.size()) columna += f[i];
        char operador = columna.back();
        if (operador == '+' || operador == '*') {  // empieza un grupo nuevo
            multiplica = operador == '*';
            en_grupo = true;
            acumulado.reset();
        }
        std::string texto = columna.substr(0, columna.size() - 1);
        texto.erase(0, texto.find_first_not_of(' '));
        texto.erase(texto.find_last_not_of(' ') + 1);
        if (texto.empty()) {  // columna vacía = fin del grupo
            if (en_grupo) total += acumulado.value_or(0);
            en_grupo = false;
            continue;
        }
        Entero valor = a_entero(texto);
        acumulado = !acumulado ? valor : multiplica ? *acumulado * valor : *acumulado + valor;
    }
    if (en_grupo) total += acumulado.value_or(0);  // el último grupo no tiene columna vacía detrás
    return ans(total);
}

}  // namespace

AOC_REGISTER(2025, 6, part1, part2);
