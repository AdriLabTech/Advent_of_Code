#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iomanip>
#include <iostream>

#include "aoc.hpp"

namespace fs = std::filesystem;

static const char* BAR = "============================================================";

static fs::path input_path(int year, int day, bool example) {
    const char* env = std::getenv("AOC_INPUTS_DIR");
    fs::path base = env ? fs::path(env) : fs::path(AOC_DEFAULT_INPUTS_DIR);
    char name[32];
    std::snprintf(name, sizeof name, "day%02d%s.txt", day, example ? ".example" : "");
    return base / std::to_string(year) / name;
}

static bool run_day(const aoc::Day& d, bool example) {
    fs::path path = input_path(d.year, d.day, example);
    std::ifstream in(path);
    if (!in) {
        std::cout << "No encuentro el input: " << path.string() << "\n";
        return false;
    }
    aoc::Lines lines;
    for (std::string line; std::getline(in, line);) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        lines.push_back(line);
    }

    std::printf("\n%s\n🎄 Advent of Code %d - Día %02d%s 🎄\n%s\n", BAR, d.year, d.day, example ? " (ejemplo)" : "", BAR);
    auto start = std::chrono::steady_clock::now();
    aoc::Answer r1 = d.part1(lines);
    aoc::Answer r2 = d.part2(lines);
    double ms = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - start).count();
    std::cout << "Parte 1: " << r1.value_or("-") << "\n";
    std::cout << "Parte 2: " << r2.value_or("-") << "\n";
    std::cout << "Tiempo: " << std::fixed << std::setprecision(1) << ms << " ms\n";
    return true;
}

int main(int argc, char** argv) {
    bool example = false;
    std::vector<int> nums;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "--example") example = true;
        else if (!a.empty() && std::all_of(a.begin(), a.end(), ::isdigit)) nums.push_back(std::stoi(a));
    }
    if (nums.empty()) {
        std::cerr << "Uso: aoc <año> [día] [--example]\n";
        return 2;
    }

    std::vector<aoc::Day> days;
    for (const auto& d : aoc::registry())
        if (d.year == nums[0] && (nums.size() < 2 || d.day == nums[1])) days.push_back(d);
    std::sort(days.begin(), days.end(), [](auto& a, auto& b) { return a.day < b.day; });

    if (days.empty()) {
        std::cout << "No hay días implementados para ese año/día (crea uno con scripts/new_day.py)\n";
        return 1;
    }
    int done = 0;
    for (const auto& d : days) done += run_day(d, example);
    if (nums.size() == 1)
        std::printf("\n%s\nADVENT OF CODE %d: %d/%zu días ejecutados\n%s\n", BAR, nums[0], done, days.size(), BAR);
    return done == 0 ? 1 : 0;
}
