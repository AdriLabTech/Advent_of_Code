// Advent of Code 2015 - Día 13
#include <algorithm>
#include <climits>
#include <functional>
#include <map>
#include <sstream>

#include "aoc.hpp"

using namespace aoc;

namespace {

using Felicidad = std::map<std::pair<std::string, std::string>, int>;

// 'A would gain/lose N happiness units by sitting next to B.' -> felicidad[(A, B)] y lista de invitados.
void leer(const Lines& lines, Felicidad& f, std::vector<std::string>& invitados) {
    for (auto l : lines) {
        while (!l.empty() && (l.back() == '.' || l.back() == '\r')) l.pop_back();
        std::stringstream ss(l);
        std::vector<std::string> p;
        for (std::string t; ss >> t;) p.push_back(t);
        if (p.size() < 11) continue;
        int n = std::stoi(p[3]);
        f[{p[0], p.back()}] = p[2] == "gain" ? n : -n;
        if (std::find(invitados.begin(), invitados.end(), p[0]) == invitados.end()) invitados.push_back(p[0]);
    }
}

// Mayor suma de felicidad en una mesa redonda (cada pareja de vecinos cuenta en los dos sentidos).
int mejor_mesa(const Felicidad& f, std::vector<std::string> invitados) {
    std::sort(invitados.begin(), invitados.end());
    auto valor = [&](int a, int b) {
        auto x = f.find({invitados[a], invitados[b]}), y = f.find({invitados[b], invitados[a]});
        return (x == f.end() ? 0 : x->second) + (y == f.end() ? 0 : y->second);
    };
    std::vector<int> mesa(invitados.size());
    for (std::size_t i = 0; i < mesa.size(); ++i) mesa[i] = static_cast<int>(i);
    int mejor = INT_MIN;
    std::function<void(std::size_t)> permutar = [&](std::size_t desde) {
        if (desde == mesa.size()) {
            int total = 0;
            for (std::size_t i = 0; i < mesa.size(); ++i) total += valor(mesa[i], mesa[(i + 1) % mesa.size()]);
            mejor = std::max(mejor, total);
            return;
        }
        for (std::size_t i = desde; i < mesa.size(); ++i) {
            std::swap(mesa[desde], mesa[i]);
            permutar(desde + 1);
            std::swap(mesa[desde], mesa[i]);
        }
    };
    permutar(1);  // la mesa es circular: fijar el primero evita repetir giros
    return mejor;
}

Answer part1(const Lines& lines) {
    Felicidad f;
    std::vector<std::string> invitados;
    leer(lines, f, invitados);
    return ans(mejor_mesa(f, invitados));
}

Answer part2(const Lines& lines) {
    Felicidad f;
    std::vector<std::string> invitados;
    leer(lines, f, invitados);
    invitados.push_back("Yo");  // yo me siento con felicidad 0 con todos
    return ans(mejor_mesa(f, invitados));
}

}  // namespace

AOC_REGISTER(2015, 13, part1, part2);
