"""Advent of Code 2015 - Día 21"""
from itertools import combinations
from aoc import ints

# (coste, daño, armadura) de la tienda
ARMAS = [(8, 4, 0), (10, 5, 0), (25, 6, 0), (40, 7, 0), (74, 8, 0)]
ARMADURAS = [(0, 0, 0), (13, 0, 1), (31, 0, 2), (53, 0, 3), (75, 0, 4), (102, 0, 5)]  # la primera = sin armadura
ANILLOS = [(25, 1, 0), (50, 2, 0), (100, 3, 0), (20, 0, 1), (40, 0, 2), (80, 0, 3)]


def gana_jugador(vida: int, dano: int, armadura: int, jefe: tuple[int, int, int]) -> bool:
    """Gana quien tarda menos turnos en matar al otro (el jugador pega primero, así que gana en un empate)."""
    vida_jefe, dano_jefe, armadura_jefe = jefe
    turnos_jugador = -(-vida_jefe // max(1, dano - armadura_jefe))
    turnos_jefe = -(-vida // max(1, dano_jefe - armadura))
    return turnos_jugador <= turnos_jefe


def equipamientos():
    """(coste, daño, armadura) de cada compra posible: 1 arma, 0-1 armadura y 0-2 anillos."""
    for arma in ARMAS:
        for armadura in ARMADURAS:
            for cuantos in range(3):
                for anillos in combinations(ANILLOS, cuantos):
                    items = (arma, armadura, *anillos)
                    yield tuple(sum(i[k] for i in items) for k in range(3))


def part1(lines: list[str]):
    jefe = tuple(ints(" ".join(lines)))
    return min(c for c, d, a in equipamientos() if gana_jugador(100, d, a, jefe))  # type: ignore[arg-type]


def part2(lines: list[str]):
    jefe = tuple(ints(" ".join(lines)))
    return max(c for c, d, a in equipamientos() if not gana_jugador(100, d, a, jefe))  # type: ignore[arg-type]
