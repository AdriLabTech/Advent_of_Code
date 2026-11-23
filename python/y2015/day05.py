"""Advent of Code 2015 - Día 5"""


def es_buena_v1(s: str) -> bool:
    vocales = sum(c in "aeiou" for c in s) >= 3
    doble = any(a == b for a, b in zip(s, s[1:]))
    prohibida = any(p in s for p in ("ab", "cd", "pq", "xy"))
    return vocales and doble and not prohibida


def es_buena_v2(s: str) -> bool:
    # un par de letras que reaparece más adelante sin solaparse
    par_repetido = any(s.find(s[i : i + 2], i + 2) != -1 for i in range(len(s) - 1))
    # una letra que se repite con otra en medio (xyx)
    letra_entre = any(a == b for a, b in zip(s, s[2:]))
    return par_repetido and letra_entre


def part1(lines: list[str]):
    return sum(es_buena_v1(line) for line in lines)


def part2(lines: list[str]):
    return sum(es_buena_v2(line) for line in lines)
