"""Advent of Code 2015 - Día 18"""

PASOS = 100
PASOS_EJEMPLO = (4, 5)  # el ejemplo del enunciado (6x6) usa 4 pasos en la parte 1 y 5 en la parte 2


def leer(lines: list[str]) -> tuple[set[tuple[int, int]], int]:
    filas = [l.strip() for l in lines if l.strip()]
    return {(r, c) for r, fila in enumerate(filas) for c, ch in enumerate(fila) if ch == "#"}, len(filas)


def paso(encendidas: set[tuple[int, int]], lado: int) -> set[tuple[int, int]]:
    """Una generación del juego de la vida (los vecinos fuera de la rejilla cuentan como apagados)."""
    vecinos: dict[tuple[int, int], int] = {}
    for r, c in encendidas:
        for dr in (-1, 0, 1):
            for dc in (-1, 0, 1):
                if (dr or dc) and 0 <= r + dr < lado and 0 <= c + dc < lado:
                    vecinos[(r + dr, c + dc)] = vecinos.get((r + dr, c + dc), 0) + 1
    return {p for p, n in vecinos.items() if n == 3 or (n == 2 and p in encendidas)}


def animar(lines: list[str], pasos: tuple[int, int], esquinas_fijas: bool) -> int:
    encendidas, lado = leer(lines)
    cuantos = pasos[1 if esquinas_fijas else 0]
    esquinas = {(0, 0), (0, lado - 1), (lado - 1, 0), (lado - 1, lado - 1)}
    if esquinas_fijas:
        encendidas |= esquinas
    for _ in range(cuantos):
        encendidas = paso(encendidas, lado)
        if esquinas_fijas:
            encendidas |= esquinas  # las cuatro esquinas están atascadas encendidas
    return len(encendidas)


def part1(lines: list[str]):
    return animar(lines, PASOS_EJEMPLO if len(lines) <= 6 else (PASOS, PASOS), False)


def part2(lines: list[str]):
    return animar(lines, PASOS_EJEMPLO if len(lines) <= 6 else (PASOS, PASOS), True)
