"""Advent of Code 2015 - Día 15"""
from aoc import ints

CUCHARADAS = 100


def repartos(ingredientes: int, total: int):
    """Todas las formas de repartir `total` cucharadas entre `ingredientes` ingredientes (enteros >= 0)."""
    if ingredientes == 1:
        yield (total,)
        return
    for primero in range(total + 1):
        for resto in repartos(ingredientes - 1, total - primero):
            yield (primero, *resto)


def mejor_galleta(lines: list[str], calorias: int | None) -> int:
    ingredientes = [ints(line.split(":")[1]) for line in lines if line.strip()]  # capacidad, durabilidad, sabor, textura, calorías
    mejor = 0
    for reparto in repartos(len(ingredientes), CUCHARADAS):
        propiedades = [sum(c * ing[k] for c, ing in zip(reparto, ingredientes)) for k in range(5)]
        if calorias is not None and propiedades[4] != calorias:
            continue
        puntuacion = 1
        for p in propiedades[:4]:
            puntuacion *= max(p, 0)  # un total negativo cuenta como 0
        mejor = max(mejor, puntuacion)
    return mejor


def part1(lines: list[str]):
    return mejor_galleta(lines, None)


def part2(lines: list[str]):
    return mejor_galleta(lines, 500)
