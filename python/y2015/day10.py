"""Advent of Code 2015 - Día 10"""
from itertools import groupby


def mirar_y_decir(texto: str, veces: int) -> str:
    """Cada tanda de dígitos iguales se sustituye por (cuántos)(qué dígito)."""
    for _ in range(veces):
        texto = "".join(f"{len(list(tanda))}{digito}" for digito, tanda in groupby(texto))
    return texto


def part1(lines: list[str]):
    return len(mirar_y_decir(lines[0].strip(), 40))


def part2(lines: list[str]):
    return len(mirar_y_decir(lines[0].strip(), 50))
