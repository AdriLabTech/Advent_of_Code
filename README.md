<div align="center">

# 🎄 Advent of Code

**Mis soluciones en varios lenguajes, año a año**

[![Advent of Code](https://img.shields.io/badge/Advent_of_Code-adventofcode.com-00cc00?style=for-the-badge)](https://adventofcode.com)
[![License](https://img.shields.io/badge/Licencia-MIT-blue?style=for-the-badge)](LICENSE)

![Java](https://img.shields.io/badge/Java-21-orange?logo=openjdk&logoColor=white)
![Python](https://img.shields.io/badge/Python-listo-blue?logo=python&logoColor=white)
![Rust](https://img.shields.io/badge/Rust-listo-blue?logo=rust&logoColor=white)
![C#](https://img.shields.io/badge/C%23-listo-blue?logo=csharp&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-listo-blue?logo=cplusplus&logoColor=white)

[Lenguajes](#-lenguajes) · [Progreso](#-progreso) · [Empezar](#-empezar) · [Añadir una solución](#-añadir-una-solución) · [Reglas](#-enunciados-e-inputs-no-incluidos)

</div>

---

## 🗂️ Lenguajes

Cada lenguaje usa la estructura que mejor le encaja, pero todos cumplen el mismo contrato: **un día nuevo = un fichero** y el mismo ejecutor `<año> [día] [--example]`.

| Lenguaje | Estilo | Estado | Guía |
|---|---|---|---|
| ☕ Java | POO: `Calendar` / `Day` | ✅ 2015 y 2025 completos | [java/](java/README.md) |
| 🐍 Python | Módulos y funciones, descubrimiento por nombre | ✅ 2015 y 2025 completos | [python/](python/README.md) |
| 🦀 Rust | Funciones libres, registro generado por `build.rs` | ✅ 2015 y 2025 completos | [rust/](rust/README.md) |
| 🟣 C# | Clases con reflexión (sin registro manual) | ✅ 2015 y 2025 completos | [csharp/](csharp/README.md) |
| ⚙️ C++ | Funciones libres + autorregistro con macro | ✅ 2015 y 2025 completos | [cpp/](cpp/README.md) |

Convenciones comunes: [docs/CONVENCIONES.md](docs/CONVENCIONES.md).

## ⚡ Resumen: cómo empezar una solución

1. Pon tu input en `inputs/<año>/dayNN.txt` (y, si quieres, el ejemplo en `dayNN.example.txt`).
2. Genera el esqueleto: `scripts/new_day.py <lenguaje|all> <año> <día>` (necesita Python 3).
3. Programa `part1` y `part2` en el fichero creado.
4. Ejecútalo desde la carpeta del lenguaje:

| Lenguaje | Fichero que se crea | Ejecutar (desde su carpeta) |
|---|---|---|
| ☕ Java | `src/year_YYYY/Day_NN_YYYY.java` + `src/utils_YYYY/Utils_DayNN.java` (se registra solo) | `javac -d bin $(find src -name '*.java') && java -cp bin core.Main` |
| 🐍 Python | `y2025/day03.py` | `python -m aoc 2025 3` |
| 🦀 Rust | `src/solutions/y2025/day03.rs` | `cargo run --release -- 2025 3` |
| 🟣 C# | `Solutions/Y2025/Day03.cs` | `dotnet run -c Release -- 2025 3` |
| ⚙️ C++ | `src/solutions/y2025/day03.cpp` | `cmake -B build -S . && cmake --build build && ./build/aoc 2025 3` |

Ejemplo: `scripts/new_day.py rust 2025 3` · `scripts/new_day.py all 2025 3` (todos a la vez).
Sin día = año completo; `--example` usa `dayNN.example.txt` (no disponible en Java).

## 📊 Progreso

Despliega cada sección para ver su información. Cada celda enlaza a la solución (✅) o queda pendiente (⬜); el número de día enlaza al puzzle en adventofcode.com.

<details>
<summary><b>🎅 Progreso 2025</b> — 12/12 días · 24 ⭐ · verificado en los 5 lenguajes</summary>

| Día | ☕ Java | 🐍 Python | 🦀 Rust | 🟣 C# | ⚙️ C++ |
|:---:|:---:|:---:|:---:|:---:|:---:|
| [01](https://adventofcode.com/2025/day/1) | [✅](java/src/year_2025/Day_01_2025.java) | [✅](python/y2025/day01.py) | [✅](rust/src/solutions/y2025/day01.rs) | [✅](csharp/Solutions/Y2025/Day01.cs) | [✅](cpp/src/solutions/y2025/day01.cpp) |
| [02](https://adventofcode.com/2025/day/2) | [✅](java/src/year_2025/Day_02_2025.java) | [✅](python/y2025/day02.py) | [✅](rust/src/solutions/y2025/day02.rs) | [✅](csharp/Solutions/Y2025/Day02.cs) | [✅](cpp/src/solutions/y2025/day02.cpp) |
| [03](https://adventofcode.com/2025/day/3) | [✅](java/src/year_2025/Day_03_2025.java) | [✅](python/y2025/day03.py) | [✅](rust/src/solutions/y2025/day03.rs) | [✅](csharp/Solutions/Y2025/Day03.cs) | [✅](cpp/src/solutions/y2025/day03.cpp) |
| [04](https://adventofcode.com/2025/day/4) | [✅](java/src/year_2025/Day_04_2025.java) | [✅](python/y2025/day04.py) | [✅](rust/src/solutions/y2025/day04.rs) | [✅](csharp/Solutions/Y2025/Day04.cs) | [✅](cpp/src/solutions/y2025/day04.cpp) |
| [05](https://adventofcode.com/2025/day/5) | [✅](java/src/year_2025/Day_05_2025.java) | [✅](python/y2025/day05.py) | [✅](rust/src/solutions/y2025/day05.rs) | [✅](csharp/Solutions/Y2025/Day05.cs) | [✅](cpp/src/solutions/y2025/day05.cpp) |
| [06](https://adventofcode.com/2025/day/6) | [✅](java/src/year_2025/Day_06_2025.java) | [✅](python/y2025/day06.py) | [✅](rust/src/solutions/y2025/day06.rs) | [✅](csharp/Solutions/Y2025/Day06.cs) | [✅](cpp/src/solutions/y2025/day06.cpp) |
| [07](https://adventofcode.com/2025/day/7) | [✅](java/src/year_2025/Day_07_2025.java) | [✅](python/y2025/day07.py) | [✅](rust/src/solutions/y2025/day07.rs) | [✅](csharp/Solutions/Y2025/Day07.cs) | [✅](cpp/src/solutions/y2025/day07.cpp) |
| [08](https://adventofcode.com/2025/day/8) | [✅](java/src/year_2025/Day_08_2025.java) | [✅](python/y2025/day08.py) | [✅](rust/src/solutions/y2025/day08.rs) | [✅](csharp/Solutions/Y2025/Day08.cs) | [✅](cpp/src/solutions/y2025/day08.cpp) |
| [09](https://adventofcode.com/2025/day/9) | [✅](java/src/year_2025/Day_09_2025.java) | [✅](python/y2025/day09.py) | [✅](rust/src/solutions/y2025/day09.rs) | [✅](csharp/Solutions/Y2025/Day09.cs) | [✅](cpp/src/solutions/y2025/day09.cpp) |
| [10](https://adventofcode.com/2025/day/10) | [✅](java/src/year_2025/Day_10_2025.java) | [✅](python/y2025/day10.py) | [✅](rust/src/solutions/y2025/day10.rs) | [✅](csharp/Solutions/Y2025/Day10.cs) | [✅](cpp/src/solutions/y2025/day10.cpp) |
| [11](https://adventofcode.com/2025/day/11) | [✅](java/src/year_2025/Day_11_2025.java) | [✅](python/y2025/day11.py) | [✅](rust/src/solutions/y2025/day11.rs) | [✅](csharp/Solutions/Y2025/Day11.cs) | [✅](cpp/src/solutions/y2025/day11.cpp) |
| [12](https://adventofcode.com/2025/day/12) | [✅](java/src/year_2025/Day_12_2025.java) | [✅](python/y2025/day12.py) | [✅](rust/src/solutions/y2025/day12.rs) | [✅](csharp/Solutions/Y2025/Day12.cs) | [✅](cpp/src/solutions/y2025/day12.cpp) |

</details>

<details>
<summary><b>🎅 Progreso 2015</b> — 25/25 días · 50 ⭐ · verificado en los 5 lenguajes</summary>

| Día | ☕ Java | 🐍 Python | 🦀 Rust | 🟣 C# | ⚙️ C++ |
|:---:|:---:|:---:|:---:|:---:|:---:|
| [01](https://adventofcode.com/2015/day/1) | [✅](java/src/year_2015/Day_01_2015.java) | [✅](python/y2015/day01.py) | [✅](rust/src/solutions/y2015/day01.rs) | [✅](csharp/Solutions/Y2015/Day01.cs) | [✅](cpp/src/solutions/y2015/day01.cpp) |
| [02](https://adventofcode.com/2015/day/2) | [✅](java/src/year_2015/Day_02_2015.java) | [✅](python/y2015/day02.py) | [✅](rust/src/solutions/y2015/day02.rs) | [✅](csharp/Solutions/Y2015/Day02.cs) | [✅](cpp/src/solutions/y2015/day02.cpp) |
| [03](https://adventofcode.com/2015/day/3) | [✅](java/src/year_2015/Day_03_2015.java) | [✅](python/y2015/day03.py) | [✅](rust/src/solutions/y2015/day03.rs) | [✅](csharp/Solutions/Y2015/Day03.cs) | [✅](cpp/src/solutions/y2015/day03.cpp) |
| [04](https://adventofcode.com/2015/day/4) | [✅](java/src/year_2015/Day_04_2015.java) | [✅](python/y2015/day04.py) | [✅](rust/src/solutions/y2015/day04.rs) | [✅](csharp/Solutions/Y2015/Day04.cs) | [✅](cpp/src/solutions/y2015/day04.cpp) |
| [05](https://adventofcode.com/2015/day/5) | [✅](java/src/year_2015/Day_05_2015.java) | [✅](python/y2015/day05.py) | [✅](rust/src/solutions/y2015/day05.rs) | [✅](csharp/Solutions/Y2015/Day05.cs) | [✅](cpp/src/solutions/y2015/day05.cpp) |
| [06](https://adventofcode.com/2015/day/6) | [✅](java/src/year_2015/Day_06_2015.java) | [✅](python/y2015/day06.py) | [✅](rust/src/solutions/y2015/day06.rs) | [✅](csharp/Solutions/Y2015/Day06.cs) | [✅](cpp/src/solutions/y2015/day06.cpp) |
| [07](https://adventofcode.com/2015/day/7) | [✅](java/src/year_2015/Day_07_2015.java) | [✅](python/y2015/day07.py) | [✅](rust/src/solutions/y2015/day07.rs) | [✅](csharp/Solutions/Y2015/Day07.cs) | [✅](cpp/src/solutions/y2015/day07.cpp) |
| [08](https://adventofcode.com/2015/day/8) | [✅](java/src/year_2015/Day_08_2015.java) | [✅](python/y2015/day08.py) | [✅](rust/src/solutions/y2015/day08.rs) | [✅](csharp/Solutions/Y2015/Day08.cs) | [✅](cpp/src/solutions/y2015/day08.cpp) |
| [09](https://adventofcode.com/2015/day/9) | [✅](java/src/year_2015/Day_09_2015.java) | [✅](python/y2015/day09.py) | [✅](rust/src/solutions/y2015/day09.rs) | [✅](csharp/Solutions/Y2015/Day09.cs) | [✅](cpp/src/solutions/y2015/day09.cpp) |
| [10](https://adventofcode.com/2015/day/10) | [✅](java/src/year_2015/Day_10_2015.java) | [✅](python/y2015/day10.py) | [✅](rust/src/solutions/y2015/day10.rs) | [✅](csharp/Solutions/Y2015/Day10.cs) | [✅](cpp/src/solutions/y2015/day10.cpp) |
| [11](https://adventofcode.com/2015/day/11) | [✅](java/src/year_2015/Day_11_2015.java) | [✅](python/y2015/day11.py) | [✅](rust/src/solutions/y2015/day11.rs) | [✅](csharp/Solutions/Y2015/Day11.cs) | [✅](cpp/src/solutions/y2015/day11.cpp) |
| [12](https://adventofcode.com/2015/day/12) | [✅](java/src/year_2015/Day_12_2015.java) | [✅](python/y2015/day12.py) | [✅](rust/src/solutions/y2015/day12.rs) | [✅](csharp/Solutions/Y2015/Day12.cs) | [✅](cpp/src/solutions/y2015/day12.cpp) |
| [13](https://adventofcode.com/2015/day/13) | [✅](java/src/year_2015/Day_13_2015.java) | [✅](python/y2015/day13.py) | [✅](rust/src/solutions/y2015/day13.rs) | [✅](csharp/Solutions/Y2015/Day13.cs) | [✅](cpp/src/solutions/y2015/day13.cpp) |
| [14](https://adventofcode.com/2015/day/14) | [✅](java/src/year_2015/Day_14_2015.java) | [✅](python/y2015/day14.py) | [✅](rust/src/solutions/y2015/day14.rs) | [✅](csharp/Solutions/Y2015/Day14.cs) | [✅](cpp/src/solutions/y2015/day14.cpp) |
| [15](https://adventofcode.com/2015/day/15) | [✅](java/src/year_2015/Day_15_2015.java) | [✅](python/y2015/day15.py) | [✅](rust/src/solutions/y2015/day15.rs) | [✅](csharp/Solutions/Y2015/Day15.cs) | [✅](cpp/src/solutions/y2015/day15.cpp) |
| [16](https://adventofcode.com/2015/day/16) | [✅](java/src/year_2015/Day_16_2015.java) | [✅](python/y2015/day16.py) | [✅](rust/src/solutions/y2015/day16.rs) | [✅](csharp/Solutions/Y2015/Day16.cs) | [✅](cpp/src/solutions/y2015/day16.cpp) |
| [17](https://adventofcode.com/2015/day/17) | [✅](java/src/year_2015/Day_17_2015.java) | [✅](python/y2015/day17.py) | [✅](rust/src/solutions/y2015/day17.rs) | [✅](csharp/Solutions/Y2015/Day17.cs) | [✅](cpp/src/solutions/y2015/day17.cpp) |
| [18](https://adventofcode.com/2015/day/18) | [✅](java/src/year_2015/Day_18_2015.java) | [✅](python/y2015/day18.py) | [✅](rust/src/solutions/y2015/day18.rs) | [✅](csharp/Solutions/Y2015/Day18.cs) | [✅](cpp/src/solutions/y2015/day18.cpp) |
| [19](https://adventofcode.com/2015/day/19) | [✅](java/src/year_2015/Day_19_2015.java) | [✅](python/y2015/day19.py) | [✅](rust/src/solutions/y2015/day19.rs) | [✅](csharp/Solutions/Y2015/Day19.cs) | [✅](cpp/src/solutions/y2015/day19.cpp) |
| [20](https://adventofcode.com/2015/day/20) | [✅](java/src/year_2015/Day_20_2015.java) | [✅](python/y2015/day20.py) | [✅](rust/src/solutions/y2015/day20.rs) | [✅](csharp/Solutions/Y2015/Day20.cs) | [✅](cpp/src/solutions/y2015/day20.cpp) |
| [21](https://adventofcode.com/2015/day/21) | [✅](java/src/year_2015/Day_21_2015.java) | [✅](python/y2015/day21.py) | [✅](rust/src/solutions/y2015/day21.rs) | [✅](csharp/Solutions/Y2015/Day21.cs) | [✅](cpp/src/solutions/y2015/day21.cpp) |
| [22](https://adventofcode.com/2015/day/22) | [✅](java/src/year_2015/Day_22_2015.java) | [✅](python/y2015/day22.py) | [✅](rust/src/solutions/y2015/day22.rs) | [✅](csharp/Solutions/Y2015/Day22.cs) | [✅](cpp/src/solutions/y2015/day22.cpp) |
| [23](https://adventofcode.com/2015/day/23) | [✅](java/src/year_2015/Day_23_2015.java) | [✅](python/y2015/day23.py) | [✅](rust/src/solutions/y2015/day23.rs) | [✅](csharp/Solutions/Y2015/Day23.cs) | [✅](cpp/src/solutions/y2015/day23.cpp) |
| [24](https://adventofcode.com/2015/day/24) | [✅](java/src/year_2015/Day_24_2015.java) | [✅](python/y2015/day24.py) | [✅](rust/src/solutions/y2015/day24.rs) | [✅](csharp/Solutions/Y2015/Day24.cs) | [✅](cpp/src/solutions/y2015/day24.cpp) |
| [25](https://adventofcode.com/2015/day/25) | [✅](java/src/year_2015/Day_25_2015.java) | [✅](python/y2015/day25.py) | [✅](rust/src/solutions/y2015/day25.rs) | [✅](csharp/Solutions/Y2015/Day25.cs) | [✅](cpp/src/solutions/y2015/day25.cpp) |

</details>

**Leyenda:** ✅ resuelto (enlaza al código) · ⬜ pendiente

**Totales:** 2015 y 2025 completos (74 ⭐ de 74 posibles: 50 + 24). Los 37 días están resueltos y verificados en los cinco lenguajes con las respuestas aceptadas por Advent of Code y con los ejemplos de cada enunciado. La última parte de 2015 (día 25) y la del día 12 de 2025 son estrellas finales gratuitas y no tienen puzzle.

<details>
<summary><b>⏱️ Detalles de Java</b> — dificultad y tiempos</summary>

**2025**

| Día | Título (Java) | Parte 1 | Parte 2 | Dificultad | Tiempo |
|-----|--------|:-------:|:-------:|:----------:|:------:|
| 01 | [Día 1](java/src/year_2025/Day_01_2025.java) | ✅ | ✅ | ⭐ | 30ms |
| 02 | [Día 2](java/src/year_2025/Day_02_2025.java) | ✅ | ✅ | ⭐ | 250ms |
| 03 | [Día 3](java/src/year_2025/Day_03_2025.java) | ✅ | ✅ | ⭐⭐ | 90ms |
| 04 | [Día 4](java/src/year_2025/Day_04_2025.java) | ✅ | ✅ | ⭐⭐⭐ | 26ms |
| 05 | [Día 5](java/src/year_2025/Day_05_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐⭐ | 7ms |
| 06 | [Día 6](java/src/year_2025/Day_06_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐ | 50ms |
| 07 | [Día 7](java/src/year_2025/Day_07_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐ | 28ms |
| 08 | [Día 8](java/src/year_2025/Day_08_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐⭐ | 328ms |
| 09 | [Día 9](java/src/year_2025/Day_09_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐⭐⭐ | 68ms |
| 10 | [Día 10](java/src/year_2025/Day_10_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐⭐⭐⭐⭐ | 753ms |
| 11 | [Día 11](java/src/year_2025/Day_11_2025.java) | ✅ | ✅ | ⭐⭐⭐⭐⭐⭐ | 9ms |
| 12 | [Día 12](java/src/year_2025/Day_12_2025.java) | ✅ | - | ⭐⭐⭐⭐ | 20ms |

**2015**

| Día | Título (Java) | Parte 1 | Parte 2 | Dificultad | Tiempo |
|-----|--------|:-------:|:-------:|:----------:|:------:|
| 01 | [Día 1](java/src/year_2015/Day_01_2015.java) | ✅ | ✅ | ⭐ | 17ms |

</details>

## 📁 Estructura

```
Advent_of_Code/
├── java/      # src/{core,utils,years,year_YYYY,utils_YYYY}
├── python/    # aoc/ (núcleo) + yYYYY/dayNN.py
├── rust/      # Cargo.toml, build.rs, src/{main,aoc}.rs, src/solutions/yYYYY/
├── csharp/    # AdventOfCode.csproj, Core/, Solutions/YYYYYY/
├── cpp/       # CMakeLists.txt, src/core/, src/solutions/yYYYY/
├── scripts/new_day.py                 # generador de esqueletos
├── inputs/<año>/dayNN.txt             # LOCAL, ignorado por git
├── enunciados/<año>/dayNN.md          # LOCAL, ignorado por git
├── docs/CONVENCIONES.md               # contrato común
└── .githooks/pre-commit               # protege enunciados e inputs
```

## 🚀 Empezar

```bash
git clone git@github.com:AdriLabTech/Advent_of_Code.git
cd Advent_of_Code
git config core.hooksPath .githooks   # activa la protección de enunciados/inputs
mkdir -p inputs/2025                  # copia aquí tus dayNN.txt
cd java                               # o el lenguaje que quieras; ver su README
```

## ➕ Añadir una solución

1. Genera y escribe el día (ver [el resumen](#-resumen-cómo-empezar-una-solución)).
2. En la tabla del año de este README, cambia ⬜ por `[✅](ruta/a/la/solución)` en la columna del lenguaje.
3. Año nuevo: copia un bloque `<details>` de año y cambia el título y el nº de días (el puzzle es `https://adventofcode.com/<año>/day/<n>`).
4. Lenguaje nuevo: sigue «Añadir un lenguaje nuevo» en [docs/CONVENCIONES.md](docs/CONVENCIONES.md).
5. Commit por solución, p. ej. `feat(2025): día 3 en Rust`.

## 🔒 Enunciados e inputs: no incluidos

Las normas de Advent of Code prohíben redistribuir los textos de los puzzles y los inputs. Este repositorio **no contiene** `enunciados/` ni `inputs/`: están en `.gitignore` y el hook `.githooks/pre-commit` bloquea cualquier intento de subirlos. Para ejecutar las soluciones necesitas tus propios inputs, descargados de tu cuenta en adventofcode.com.

## 🙏 Agradecimientos

Gracias a **[@gh0st_2202](https://github.com/gh0st-2202)** por su ayuda y colaboración en distintos retos de Advent of Code 2025, especialmente en la discusión de enfoques algorítmicos y optimización en Java.

## 📄 Licencia

MIT. Consulta [LICENSE](LICENSE).

---

<sub>PDT: Hay que tener un "porque", para empezar a preguntarse "como"</sub>
