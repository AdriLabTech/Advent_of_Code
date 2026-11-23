"""Advent of Code 2015 - Día 1"""


def part1(lines: list[str]):
    return lines[0].count("(") - lines[0].count(")")


def part2(lines: list[str]):
    """Posición (empezando en 1) del primer carácter que lleva al piso -1."""
    piso = 0
    for posicion, c in enumerate(lines[0], start=1):
        piso += 1 if c == "(" else -1 if c == ")" else 0
        if piso == -1:
            return posicion
    return None  # nunca entra en el sótano
