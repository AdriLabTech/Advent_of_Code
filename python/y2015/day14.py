"""Advent of Code 2015 - Día 14"""
from aoc import ints

CARRERA = 2503  # segundos de la carrera
CARRERA_EJEMPLO = 1000  # el ejemplo del enunciado (2 renos) dura 1000 s


def leer(lines: list[str]) -> list[tuple[int, int, int]]:
    """(velocidad, segundos volando, segundos descansando) de cada reno."""
    return [tuple(ints(line)) for line in lines if line.strip()]  # type: ignore[misc]


def distancia(reno: tuple[int, int, int], segundos: int) -> int:
    velocidad, vuela, descansa = reno
    ciclos, resto = divmod(segundos, vuela + descansa)
    return velocidad * (ciclos * vuela + min(resto, vuela))


def duracion(renos: list) -> int:
    return CARRERA_EJEMPLO if len(renos) <= 2 else CARRERA


def part1(lines: list[str]):
    renos = leer(lines)
    return max(distancia(r, duracion(renos)) for r in renos)


def part2(lines: list[str]):
    # cada segundo, el reno (o renos) que va en cabeza gana un punto
    renos = leer(lines)
    puntos = [0] * len(renos)
    for segundo in range(1, duracion(renos) + 1):
        distancias = [distancia(r, segundo) for r in renos]
        for i, d in enumerate(distancias):
            puntos[i] += d == max(distancias)
    return max(puntos)
