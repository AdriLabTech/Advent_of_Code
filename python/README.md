# Python

Estado: **sin empezar** (estructura preparada, ningún día resuelto).

Sigue el contrato de [../docs/CONVENCIONES.md](../docs/CONVENCIONES.md):

- Input: `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). No se versiona.
- Cada día expone `part1` y `part2` y devuelve texto.
- Ejecutor por año/día con tiempo de ejecución.

## Requisitos
- Python 3.12+

## Estructura sugerida
```
python/
├── aoc/            # lectura de input y ejecutor
└── y2025/day01.py  # part1(lines) / part2(lines)
```
Ejecución prevista: `python -m aoc 2025 1`
