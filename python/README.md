# 🐍 Python

Estilo: **funcional y sin registro**. Cada día es un módulo con dos funciones; el ejecutor lo descubre por nombre.

Requisitos: Python 3.12+ (sin dependencias).

```
python/
├── aoc/                 # núcleo: lectura de inputs, helpers y ejecutor
│   ├── io.py            #   read_lines, read_text, ints, paragraphs
│   └── runner.py        #   descubre y ejecuta y{año}/day{NN}.py
├── templates/day.py.tpl
└── y2025/day01.py       # una solución = un fichero
```

## Crear un día
```bash
scripts/new_day.py python 2025 3     # desde la raíz del repo
```
Edita `python/y2025/day03.py`: `part1(lines)` y `part2(lines)` devuelven el resultado (`None` = pendiente). Helpers: `ints(texto)`, `paragraphs(lines)`.

## Ejecutar (desde `python/`)
```bash
python -m aoc 2025 3             # un día
python -m aoc 2025               # todo el año
python -m aoc 2025 3 --example   # usa inputs/2025/day03.example.txt
```
