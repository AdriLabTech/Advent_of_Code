"""Advent of Code 2015 - Día 13"""
from itertools import permutations


def leer(lines: list[str]) -> dict[tuple[str, str], int]:
    """'A would gain/lose N happiness units by sitting next to B.' -> felicidad[(A, B)]."""
    felicidad = {}
    for line in lines:
        if line.strip():
            p = line.rstrip(".").split()
            felicidad[(p[0], p[-1])] = int(p[3]) * (1 if p[2] == "gain" else -1)
    return felicidad


def mejor_mesa(felicidad: dict[tuple[str, str], int], invitados: set[str]) -> int:
    """Mayor suma de felicidad en una mesa redonda (cada pareja de vecinos cuenta en los dos sentidos)."""
    primero, *resto = sorted(invitados)  # la mesa es circular: fijar uno evita repetir giros
    mejor = None
    for orden in permutations(resto):
        mesa = (primero, *orden)
        total = sum(felicidad.get((a, b), 0) + felicidad.get((b, a), 0) for a, b in zip(mesa, mesa[1:] + mesa[:1]))
        mejor = total if mejor is None else max(mejor, total)
    return mejor


def part1(lines: list[str]):
    felicidad = leer(lines)
    return mejor_mesa(felicidad, {a for a, _ in felicidad})


def part2(lines: list[str]):
    felicidad = leer(lines)
    return mejor_mesa(felicidad, {a for a, _ in felicidad} | {"Yo"})  # yo me siento con felicidad 0 con todos
