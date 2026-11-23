"""Advent of Code 2025 - Día 1"""

DIAL = 100  # posiciones del dial (0..99)
START = 50  # posición inicial


def rotations(lines: list[str]):
    """Convierte cada línea (L68, R48...) en un desplazamiento con signo: L = negativo, R = positivo."""
    for line in lines:
        if line.strip():
            yield (-1 if line[0] == "L" else 1) * int(line[1:])


def part1(lines: list[str]):
    pos, zeros = START, 0
    for delta in rotations(lines):
        pos = (pos + delta) % DIAL  # el módulo de Python ya es siempre positivo
        zeros += pos == 0
    return zeros


def part2(lines: list[str]):
    pos, zeros = START, 0
    for delta in rotations(lines):
        # Girar a la izquierda equivale a girar a la derecha desde la posición "espejo" (DIAL - pos).
        # Así solo hay que contar cuántas veces se cruza un múltiplo de 100 hacia delante.
        start = pos if delta > 0 else (DIAL - pos) % DIAL
        zeros += (start + abs(delta)) // DIAL
        pos = (pos + delta) % DIAL
    return zeros
