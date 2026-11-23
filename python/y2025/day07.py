"""Advent of Code 2025 - Día 7"""


def leer(lines: list[str]):
    mapa = [line for line in lines if line]
    sy, sx = next((y, row.index("S")) for y, row in enumerate(mapa) if "S" in row)
    return mapa, sy, sx


def part1(lines: list[str]):
    mapa, sy, sx = leer(lines)
    ancho, rayos, divisiones = len(mapa[0]), {sx}, 0
    for y in range(sy, len(mapa) - 1):  # el rayo baja fila a fila
        siguiente = set()
        for x in rayos:
            if mapa[y + 1][x] == "^":  # divisor: sale por los dos lados
                divisiones += 1
                siguiente |= {n for n in (x - 1, x + 1) if 0 <= n < ancho}
            else:
                siguiente.add(x)
        rayos = siguiente
    return divisiones


def part2(lines: list[str]):
    mapa, sy, sx = leer(lines)
    ancho = len(mapa[0])
    # caminos[x]: líneas temporales que salen por abajo partiendo de (x, y); se rellena de abajo arriba
    caminos = [1] * ancho
    for y in range(len(mapa) - 2, sy - 1, -1):
        caminos = [
            (caminos[x - 1] if x > 0 else 0) + (caminos[x + 1] if x < ancho - 1 else 0)
            if mapa[y + 1][x] == "^"
            else caminos[x]
            for x in range(ancho)
        ]
    return caminos[sx]
