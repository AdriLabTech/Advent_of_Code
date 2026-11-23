"""Advent of Code 2015 - Día 9"""
from itertools import permutations


def longitudes_de_rutas(lines: list[str]):
    """Longitud de cada recorrido que visita todas las ciudades exactamente una vez (hay pocas: se prueban todas)."""
    distancias: dict[frozenset[str], int] = {}
    for line in lines:
        if line.strip():
            ciudades, _, numero = line.partition(" = ")
            a, b = ciudades.split(" to ")
            distancias[frozenset((a, b))] = int(numero)
    todas = set().union(*distancias)
    for ruta in permutations(todas):
        yield sum(distancias[frozenset(par)] for par in zip(ruta, ruta[1:]))


def part1(lines: list[str]):
    return min(longitudes_de_rutas(lines))


def part2(lines: list[str]):
    return max(longitudes_de_rutas(lines))
