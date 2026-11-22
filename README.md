# 🎄 Advent of Code — Soluciones multilenguaje

[![Advent of Code](https://img.shields.io/badge/Advent_of_Code-Multi_Year-blueviolet)](https://adventofcode.com)
[![License](https://img.shields.io/badge/License-MIT-blue)](LICENSE)

Mis soluciones de [Advent of Code](https://adventofcode.com) en **varios lenguajes**: Java, Python, Rust, C# y C++. Cada lenguaje vive en su propio directorio y todos comparten la misma estructura de datos y contrato de ejecución.

## Agradecimientos

Gracias a **[@gh0st_2202](https://github.com/gh0st-2202)** por su ayuda y colaboración en distintos retos de Advent of Code 2025, especialmente en la discusión de enfoques algorítmicos y optimización en Java.

## ⚠️ Enunciados e inputs: no incluidos

Las normas de Advent of Code prohíben redistribuir los textos de los puzzles y los inputs. Por eso este repositorio **no contiene** ni `enunciados/` ni `inputs/`: están en `.gitignore` y un hook de pre-commit (`.githooks/`) bloquea cualquier intento de subirlos. Para ejecutar las soluciones necesitas tus propios inputs, descargados de tu cuenta en adventofcode.com.

## 📁 Estructura

```
Advent_of_Code/
├── java/        # Proyecto Eclipse / javac (Calendar + Day)
├── python/      # preparado, sin empezar
├── rust/        # preparado, sin empezar
├── csharp/      # preparado, sin empezar
├── cpp/         # preparado, sin empezar
├── inputs/      # LOCAL (ignorado): inputs/<año>/dayNN.txt
├── enunciados/  # LOCAL (ignorado): enunciados/<año>/dayNN.md
├── docs/        # CONVENCIONES.md
└── .githooks/   # pre-commit que protege enunciados e inputs
```

Convenciones y contrato común: [docs/CONVENCIONES.md](docs/CONVENCIONES.md).

## 🚀 Empezar

```bash
git clone git@github.com:AdriLabTech/Advent_of_Code.git
cd Advent_of_Code
git config core.hooksPath .githooks      # activa la protección de enunciados/inputs
mkdir -p inputs/2025                     # y copia aquí tus dayNN.txt
```

Cada lenguaje se ejecuta desde su carpeta; ver su README ([java](java/README.md), [python](python/README.md), [rust](rust/README.md), [csharp](csharp/README.md), [cpp](cpp/README.md)).

## 📊 Progreso de Soluciones

### Advent of Code 2025

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

### Advent of Code 2015

| Día | Título (Java) | Parte 1 | Parte 2 | Dificultad | Tiempo |
|-----|--------|:-------:|:-------:|:----------:|:------:|
| 01 | [Día 1](java/src/year_2015/Day_01_2015.java) | ✅ | ✅ | ⭐ | 17ms |


**Leyenda:** ✅ Completado | - Pendiente

Progreso por lenguaje:

| Lenguaje | Estado |
|----------|--------|
| Java | 2025: 12/12 días (23/24 partes) · 2015: 6 días |
| Python, Rust, C#, C++ | Sin empezar |

## 🔗 Recursos

- [Advent of Code](https://adventofcode.com) · [r/adventofcode](https://www.reddit.com/r/adventofcode/) · [Awesome Advent of Code](https://github.com/Bogdanp/awesome-advent-of-code)

## 📄 Licencia

MIT. Consulta [LICENSE](LICENSE).

---

PDT: Hay que tener un "porque", para empezar a preguntarse "como"
