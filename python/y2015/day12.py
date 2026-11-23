"""Advent of Code 2015 - Día 12"""
from aoc import ints


def suma_sin_rojos(texto: str) -> int:
    """Suma de todos los números ignorando los objetos {...} que tengan algún valor "red" (los arrays no cuentan como objeto).

    Se recorre el texto con una pila: cada { o [ abre un nivel con su suma; al cerrarlo se suma al nivel de fuera
    (salvo un objeto con "red", que aporta 0)."""
    pila: list[list] = [[0, False, False]]  # [suma, es_objeto, tiene_rojo]
    i = 0
    while i < len(texto):
        c = texto[i]
        if c in "{[":
            pila.append([0, c == "{", False])
        elif c in "}]":
            suma, _, rojo = pila.pop()
            pila[-1][0] += 0 if rojo else suma
        elif c == '"':
            fin = texto.index('"', i + 1)
            palabra, i = texto[i + 1 : fin], fin
            siguiente = texto[i + 1 : i + 2]  # un ':' detrás significa que era una clave, no un valor
            if palabra == "red" and pila[-1][1] and siguiente != ":":
                pila[-1][2] = True
        elif c == "-" or c.isdigit():
            fin = i + 1
            while fin < len(texto) and texto[fin].isdigit():
                fin += 1
            pila[-1][0] += int(texto[i:fin])
            i = fin - 1
        i += 1
    return pila[0][0]


def part1(lines: list[str]):
    return sum(ints(lines[0]))


def part2(lines: list[str]):
    return suma_sin_rojos(lines[0])
