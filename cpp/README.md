# C++

Estado: **sin empezar** (estructura preparada, ningún día resuelto).

Sigue el contrato de [../docs/CONVENCIONES.md](../docs/CONVENCIONES.md):

- Input: `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). No se versiona.
- Cada día expone `part1` y `part2` y devuelve texto.
- Ejecutor por año/día con tiempo de ejecución.

## Requisitos
- Compilador C++20 (g++/clang++) y CMake

## Estructura sugerida
```
cpp/
├── CMakeLists.txt
└── src/y2025/day01.cpp
```
Ejecución prevista: `cmake -B build && cmake --build build && ./build/aoc 2025 1`
