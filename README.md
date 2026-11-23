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
| ☕ Java | POO: `Calendar` / `Day` | ✅ En uso (2025 completo, 2015 en curso) | [java/](java/README.md) |
| 🐍 Python | Módulos y funciones, descubrimiento por nombre | 🟢 Estructura lista | [python/](python/README.md) |
| 🦀 Rust | Funciones libres, registro generado por `build.rs` | 🟢 Estructura lista | [rust/](rust/README.md) |
| 🟣 C# | Clases con reflexión (sin registro manual) | 🟢 Estructura lista | [csharp/](csharp/README.md) |
| ⚙️ C++ | Funciones libres + autorregistro con macro | 🟢 Estructura lista | [cpp/](cpp/README.md) |

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
<summary><b>🎅 Progreso 2025</b> — Java 12/12 días</summary>

| Día | ☕ Java | 🐍 Python | 🦀 Rust | 🟣 C# | ⚙️ C++ |
|:---:|:---:|:---:|:---:|:---:|:---:|
| [01](https://adventofcode.com/2025/day/1) | [✅](java/src/year_2025/Day_01_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [02](https://adventofcode.com/2025/day/2) | [✅](java/src/year_2025/Day_02_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [03](https://adventofcode.com/2025/day/3) | [✅](java/src/year_2025/Day_03_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [04](https://adventofcode.com/2025/day/4) | [✅](java/src/year_2025/Day_04_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [05](https://adventofcode.com/2025/day/5) | [✅](java/src/year_2025/Day_05_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [06](https://adventofcode.com/2025/day/6) | [✅](java/src/year_2025/Day_06_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [07](https://adventofcode.com/2025/day/7) | [✅](java/src/year_2025/Day_07_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [08](https://adventofcode.com/2025/day/8) | [✅](java/src/year_2025/Day_08_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [09](https://adventofcode.com/2025/day/9) | [✅](java/src/year_2025/Day_09_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [10](https://adventofcode.com/2025/day/10) | [✅](java/src/year_2025/Day_10_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [11](https://adventofcode.com/2025/day/11) | [✅](java/src/year_2025/Day_11_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [12](https://adventofcode.com/2025/day/12) | [✅](java/src/year_2025/Day_12_2025.java) | ⬜ | ⬜ | ⬜ | ⬜ |

</details>

<details>
<summary><b>🎅 Progreso 2015</b> — Java 6/25 días</summary>

| Día | ☕ Java | 🐍 Python | 🦀 Rust | 🟣 C# | ⚙️ C++ |
|:---:|:---:|:---:|:---:|:---:|:---:|
| [01](https://adventofcode.com/2015/day/1) | [✅](java/src/year_2015/Day_01_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [02](https://adventofcode.com/2015/day/2) | [✅](java/src/year_2015/Day_02_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [03](https://adventofcode.com/2015/day/3) | [✅](java/src/year_2015/Day_03_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [04](https://adventofcode.com/2015/day/4) | [✅](java/src/year_2015/Day_04_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [05](https://adventofcode.com/2015/day/5) | [✅](java/src/year_2015/Day_05_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [06](https://adventofcode.com/2015/day/6) | [✅](java/src/year_2015/Day_06_2015.java) | ⬜ | ⬜ | ⬜ | ⬜ |
| [07](https://adventofcode.com/2015/day/7) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [08](https://adventofcode.com/2015/day/8) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [09](https://adventofcode.com/2015/day/9) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [10](https://adventofcode.com/2015/day/10) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [11](https://adventofcode.com/2015/day/11) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [12](https://adventofcode.com/2015/day/12) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [13](https://adventofcode.com/2015/day/13) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [14](https://adventofcode.com/2015/day/14) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [15](https://adventofcode.com/2015/day/15) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [16](https://adventofcode.com/2015/day/16) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [17](https://adventofcode.com/2015/day/17) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [18](https://adventofcode.com/2015/day/18) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [19](https://adventofcode.com/2015/day/19) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [20](https://adventofcode.com/2015/day/20) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [21](https://adventofcode.com/2015/day/21) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [22](https://adventofcode.com/2015/day/22) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [23](https://adventofcode.com/2015/day/23) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [24](https://adventofcode.com/2015/day/24) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |
| [25](https://adventofcode.com/2015/day/25) | ⬜ | ⬜ | ⬜ | ⬜ | ⬜ |

</details>

**Leyenda:** ✅ resuelto (enlaza al código) · ⬜ pendiente

**Totales:** ☕ Java 18 días (2025: 12/12 · 2015: 6/25) · resto de lenguajes: 0.

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
