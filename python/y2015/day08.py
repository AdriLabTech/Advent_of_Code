"""Advent of Code 2015 - Día 8"""
import re


def en_memoria(literal: str) -> int:
    """Caracteres del valor de un literal: cada escape (\\\\, \\", \\xNN) cuenta como uno; las comillas exteriores no cuentan."""
    return len(re.sub(r'\\(x[0-9a-f]{2}|.)', "X", literal[1:-1]))


def codificado(literal: str) -> int:
    """Caracteres de la cadena codificada de nuevo: comillas exteriores y \\ y \" escapadas."""
    return len(literal) + 2 + literal.count("\\") + literal.count('"')


def part1(lines: list[str]):
    return sum(len(l) - en_memoria(l) for l in map(str.strip, lines) if l)


def part2(lines: list[str]):
    return sum(codificado(l) - len(l) for l in map(str.strip, lines) if l)
