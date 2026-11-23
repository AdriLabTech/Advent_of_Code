"""Advent of Code 2015 - Día 3"""

MOVIMIENTOS = {"^": (0, 1), "v": (0, -1), ">": (1, 0), "<": (-1, 0)}


def casas_visitadas(ruta: str, repartidores: int) -> int:
    """Los repartidores se turnan: el movimiento i lo hace el repartidor i % repartidores."""
    posiciones = [(0, 0)] * repartidores
    visitadas = {(0, 0)}
    for i, c in enumerate(ruta):
        if c in MOVIMIENTOS:
            quien = i % repartidores
            x, y = posiciones[quien]
            dx, dy = MOVIMIENTOS[c]
            posiciones[quien] = (x + dx, y + dy)
            visitadas.add(posiciones[quien])
    return len(visitadas)


def part1(lines: list[str]):
    return casas_visitadas(lines[0], 1)


def part2(lines: list[str]):
    return casas_visitadas(lines[0], 2)
