"""Advent of Code 2015 - Día 2"""


def cajas(lines: list[str]):
    """Cada línea 'AxBxC' como (a, b, c) con a <= b <= c."""
    for line in lines:
        if line.strip():
            yield sorted(int(n) for n in line.split("x"))


def part1(lines: list[str]):
    # superficie total + el lado más pequeño (a*b) como holgura
    return sum(2 * (a * b + b * c + a * c) + a * b for a, b, c in cajas(lines))


def part2(lines: list[str]):
    # perímetro de la cara más pequeña + volumen
    return sum(2 * (a + b) + a * b * c for a, b, c in cajas(lines))
