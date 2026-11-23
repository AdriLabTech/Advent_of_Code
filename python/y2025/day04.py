"""Advent of Code 2025 - Día 4"""

VECINOS = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]


def accesibles(rollos: set[tuple[int, int]]) -> list[tuple[int, int]]:
    """Rollos '@' con menos de 4 rollos vecinos."""
    return [(r, c) for r, c in rollos if sum((r + dr, c + dc) in rollos for dr, dc in VECINOS) < 4]


def leer_rollos(lines: list[str]) -> set[tuple[int, int]]:
    return {(r, c) for r, line in enumerate(lines) for c, ch in enumerate(line) if ch == "@"}


def part1(lines: list[str]):
    return len(accesibles(leer_rollos(lines)))


def part2(lines: list[str]):
    rollos = leer_rollos(lines)
    quitados = 0
    while retirar := accesibles(rollos):  # se repite hasta que no quede ninguno accesible
        rollos.difference_update(retirar)
        quitados += len(retirar)
    return quitados
