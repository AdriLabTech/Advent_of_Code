"""Advent of Code 2025 - Día 9"""
from collections import deque
from itertools import combinations


def leer(lines: list[str]) -> list[tuple[int, int]]:
    return [tuple(int(v) for v in line.split(",")) for line in lines if line.strip()]  # type: ignore[misc]


def area(p1: tuple[int, int], p2: tuple[int, int]) -> int:
    return (abs(p1[0] - p2[0]) + 1) * (abs(p1[1] - p2[1]) + 1)


def part1(lines: list[str]):
    return max(area(a, b) for a, b in combinations(set(leer(lines)), 2))


def part2(lines: list[str]):
    rojas = leer(lines)

    # 1) Compresión de coordenadas: solo importan los valores usados (y sus vecinos, para tener borde exterior)
    xs = sorted({x + d for x, _ in rojas for d in (-1, 0, 1)})
    ys = sorted({y + d for _, y in rojas for d in (-1, 0, 1)})
    ix, iy = {x: i for i, x in enumerate(xs)}, {y: i for i, y in enumerate(ys)}
    alto, ancho = len(ys), len(xs)

    # 2) Borde del polígono (los lados unen cada punto con el siguiente)
    borde = [[False] * ancho for _ in range(alto)]
    for (x1, y1), (x2, y2) in zip(rojas, rojas[1:] + rojas[:1]):
        for y in range(min(iy[y1], iy[y2]), max(iy[y1], iy[y2]) + 1):
            for x in range(min(ix[x1], ix[x2]), max(ix[x1], ix[x2]) + 1):
                borde[y][x] = True

    # 3) Relleno desde fuera: lo que no se alcanza está dentro del polígono
    exterior = [[False] * ancho for _ in range(alto)]
    cola = deque()
    for y in range(alto):
        for x in range(ancho):
            if (y in (0, alto - 1) or x in (0, ancho - 1)) and not borde[y][x]:
                exterior[y][x] = True
                cola.append((y, x))
    while cola:
        y, x = cola.popleft()
        for ny, nx in ((y - 1, x), (y + 1, x), (y, x - 1), (y, x + 1)):
            if 0 <= ny < alto and 0 <= nx < ancho and not borde[ny][nx] and not exterior[ny][nx]:
                exterior[ny][nx] = True
                cola.append((ny, nx))

    # 4) Sumas acumuladas 2D de las celdas permitidas (borde o interior)
    suma = [[0] * (ancho + 1) for _ in range(alto + 1)]
    for y in range(alto):
        for x in range(ancho):
            permitida = borde[y][x] or not exterior[y][x]
            suma[y + 1][x + 1] = suma[y][x + 1] + suma[y + 1][x] - suma[y][x] + permitida

    # 5) Mayor rectángulo cuyas celdas están todas permitidas
    mejor = 0
    for p1, p2 in combinations(rojas, 2):
        a = area(p1, p2)
        if a <= mejor:
            continue
        x1, x2 = sorted((ix[p1[0]], ix[p2[0]]))
        y1, y2 = sorted((iy[p1[1]], iy[p2[1]]))
        dentro = suma[y2 + 1][x2 + 1] - suma[y1][x2 + 1] - suma[y2 + 1][x1] + suma[y1][x1]
        if dentro == (x2 - x1 + 1) * (y2 - y1 + 1):
            mejor = a
    return mejor
