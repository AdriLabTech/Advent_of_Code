"""Advent of Code 2015 - Día 4 (el input es la clave secreta, p. ej. una sola línea de texto)"""
from hashlib import md5


def primer_numero(clave: str, ceros: int) -> int:
    prefijo = "0" * ceros
    n = 1
    while not md5(f"{clave}{n}".encode()).hexdigest().startswith(prefijo):
        n += 1
    return n


def part1(lines: list[str]):
    return primer_numero(lines[0].strip(), 5)


def part2(lines: list[str]):
    return primer_numero(lines[0].strip(), 6)
