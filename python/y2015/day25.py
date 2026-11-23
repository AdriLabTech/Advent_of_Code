"""Advent of Code 2015 - Día 25 (el input es 'Enter the code at row R, column C.')"""
from aoc import ints

PRIMER_CODIGO = 20151125
MULTIPLICADOR = 252533
MODULO = 33554393


def codigo(fila: int, columna: int) -> int:
    """Código de la casilla (fila, columna): el papel se rellena por diagonales, así que primero se halla el
    número de orden n de la casilla y luego se aplica n-1 veces el generador (con pow modular, sin bucle)."""
    diagonal = fila + columna - 1  # nº de diagonal; las anteriores contienen 1 + 2 + ... + (diagonal-1) casillas
    n = (diagonal - 1) * diagonal // 2 + columna
    return PRIMER_CODIGO * pow(MULTIPLICADOR, n - 1, MODULO) % MODULO


def part1(lines: list[str]):
    fila, columna = ints(lines[0])
    return codigo(fila, columna)


def part2(lines: list[str]):
    return None  # la parte 2 es la estrella final gratuita (no tiene puzzle)
