"""Advent of Code 2015 - Día 6"""
from aoc import ints

LADO = 1000


def instrucciones(lines: list[str]):
    """Devuelve (accion, x1, y1, x2, y2) con x1<=x2 e y1<=y2."""
    for line in lines:
        if not line.strip():
            continue
        accion = "on" if line.startswith("turn on") else "off" if line.startswith("turn off") else "toggle"
        x1, y1, x2, y2 = ints(line)
        yield accion, min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2)


def part1(lines: list[str]):
    # cada fila es un entero usado como máscara de bits: una operación por fila
    filas = [0] * LADO
    for accion, x1, y1, x2, y2 in instrucciones(lines):
        mascara = ((1 << (x2 - x1 + 1)) - 1) << x1
        for y in range(y1, y2 + 1):
            if accion == "on":
                filas[y] |= mascara
            elif accion == "off":
                filas[y] &= ~mascara
            else:
                filas[y] ^= mascara
    return sum(fila.bit_count() for fila in filas)


def part2(lines: list[str]):
    brillo = [[0] * LADO for _ in range(LADO)]
    for accion, x1, y1, x2, y2 in instrucciones(lines):
        for y in range(y1, y2 + 1):
            fila = brillo[y]
            if accion == "on":
                fila[x1 : x2 + 1] = [v + 1 for v in fila[x1 : x2 + 1]]
            elif accion == "off":
                fila[x1 : x2 + 1] = [v - 1 if v > 0 else 0 for v in fila[x1 : x2 + 1]]
            else:
                fila[x1 : x2 + 1] = [v + 2 for v in fila[x1 : x2 + 1]]
    return sum(map(sum, brillo))
