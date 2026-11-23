"""Advent of Code 2025 - Día 11"""
import sys
from functools import cache

sys.setrecursionlimit(100_000)

OBLIGATORIOS = ("dac", "fft")


def leer(lines: list[str]) -> dict[str, list[str]]:
    grafo = {}
    for line in lines:
        if line.strip():
            nombre, _, salidas = line.partition(":")
            grafo[nombre.strip()] = salidas.split()
    return grafo


def part1(lines: list[str]):
    grafo = leer(lines)

    @cache
    def caminos(nodo: str) -> int:
        return 1 if nodo == "out" else sum(caminos(s) for s in grafo.get(nodo, []))

    return caminos("you")


def part2(lines: list[str]):
    grafo = leer(lines)

    @cache
    def caminos(nodo: str, pendientes: frozenset[str]) -> int:
        if nodo == "out":
            return 1 if not pendientes else 0  # solo vale si pasó por todos los obligatorios
        pendientes = pendientes - {nodo}
        return sum(caminos(s, pendientes) for s in grafo.get(nodo, []))

    return caminos("svr", frozenset(OBLIGATORIOS))
