"""Advent of Code 2015 - Día 24"""
from itertools import combinations
from math import prod


def se_puede_repartir(paquetes: tuple[int, ...], grupos: int, peso: int) -> bool:
    """¿Se pueden repartir los paquetes en `grupos` grupos de `peso` cada uno?"""
    if grupos == 1:
        return sum(paquetes) == peso
    for tamano in range(1, len(paquetes) + 1):
        for grupo in combinations(paquetes, tamano):
            if sum(grupo) == peso and se_puede_repartir(tuple(p for p in paquetes if p not in grupo), grupos - 1, peso):
                return True
    return False


def mejor_entrelazamiento(lines: list[str], grupos: int) -> int:
    paquetes = tuple(int(l) for l in lines if l.strip())  # los pesos son todos distintos
    peso = sum(paquetes) // grupos
    for tamano in range(1, len(paquetes) + 1):  # el primer grupo, con los menos paquetes posibles
        candidatos = [
            prod(grupo)
            for grupo in combinations(paquetes, tamano)
            if sum(grupo) == peso and se_puede_repartir(tuple(p for p in paquetes if p not in grupo), grupos - 1, peso)
        ]
        if candidatos:
            return min(candidatos)  # y entre esos, el de menor entrelazamiento cuántico (producto)
    raise ValueError("no hay reparto posible")


def part1(lines: list[str]):
    return mejor_entrelazamiento(lines, 3)


def part2(lines: list[str]):
    return mejor_entrelazamiento(lines, 4)
