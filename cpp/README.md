# ⚙️ C++

Estilo: **funciones libres + autorregistro** (sin clases ni herencia). Cada día define `part1`/`part2` y una línea `AOC_REGISTER(año, día, part1, part2)`; CMake compila automáticamente todo lo que haya en `src/solutions/`.

Requisitos: compilador C++20 (g++/clang++) y CMake 3.20+.

```
cpp/
├── CMakeLists.txt
├── src/
│   ├── core/
│   │   ├── aoc.hpp      # registro, AOC_REGISTER, ans, ints, paragraphs
│   │   └── main.cpp     # CLI y ejecutor
│   └── solutions/y2025/day01.cpp   # una solución = un fichero
└── templates/day.cpp.tpl
```

## Crear un día
```bash
scripts/new_day.py cpp 2025 3        # desde la raíz del repo
```
Edita `part1(const Lines&)` y `part2`; devuelven `ans(resultado)` (`std::nullopt` = pendiente).

## Compilar y ejecutar (desde `cpp/`)
```bash
cmake -B build -S . && cmake --build build
./build/aoc 2025 3
./build/aoc 2025               # todo el año
./build/aoc 2025 3 --example
```
Tras crear un día nuevo basta con volver a ejecutar `cmake --build build`.
