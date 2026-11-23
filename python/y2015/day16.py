"""Advent of Code 2015 - Día 16"""
import operator
import re

HUELLA = {"children": 3, "cats": 7, "samoyeds": 2, "pomeranians": 3, "akitas": 0, "vizslas": 0, "goldfish": 5, "trees": 3, "cars": 2, "perfumes": 1}
MAYORES = {"cats", "trees"}  # en la parte 2: el valor de la tía tiene que ser mayor que el de la huella
MENORES = {"pomeranians", "goldfish"}  # ... o menor


def tias(lines: list[str]):
    """(número, {compuesto: cantidad}) de cada línea 'Sue 1: goldfish: 6, trees: 9, ...'."""
    for line in lines:
        if line.strip():
            numero, *_ = re.findall(r"\d+", line.split(":")[0])
            yield int(numero), {k: int(v) for k, v in re.findall(r"(\w+): (\d+)", line.split(":", 1)[1])}


def buscar(lines: list[str], comparar) -> int:
    """La tía cuyos recuerdos cumplen `comparar(compuesto)` (una función de comparación) con la huella."""
    return next(n for n, recuerdos in tias(lines) if all(comparar(k)(v, HUELLA[k]) for k, v in recuerdos.items()))


def part1(lines: list[str]):
    return buscar(lines, lambda k: operator.eq)


def part2(lines: list[str]):
    return buscar(lines, lambda k: operator.gt if k in MAYORES else operator.lt if k in MENORES else operator.eq)
