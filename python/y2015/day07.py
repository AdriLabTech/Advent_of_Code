"""Advent of Code 2015 - Día 7"""
from functools import cache

MASCARA = 0xFFFF  # señales de 16 bits


def circuito(lines: list[str], forzado: dict[str, int] | None = None) -> dict[str, int]:
    """Señal de cada cable. `forzado` sustituye la señal de los cables indicados."""
    gates: dict[str, list[str]] = {}
    for line in lines:
        if line.strip():
            origen, destino = line.split(" -> ")
            gates[destino.strip()] = origen.split()

    @cache
    def valor(token: str) -> int:
        if token.isdigit():
            return int(token)
        if forzado and token in forzado:
            return forzado[token]
        g = gates[token]
        if len(g) == 1:  # 123 -> x  /  a -> b
            return valor(g[0])
        if len(g) == 2:  # NOT x
            return ~valor(g[1]) & MASCARA
        a, op, b = g
        if op == "AND":
            return valor(a) & valor(b)
        if op == "OR":
            return valor(a) | valor(b)
        if op == "LSHIFT":
            return (valor(a) << valor(b)) & MASCARA
        return valor(a) >> valor(b)  # RSHIFT

    return {cable: valor(cable) for cable in gates}


def part1(lines: list[str]):
    return circuito(lines).get("a")  # el ejemplo del enunciado no tiene cable a


def part2(lines: list[str]):
    # la señal de a (parte 1) se pasa al cable b y se recalcula todo
    a = part1(lines)
    return None if a is None else circuito(lines, {"b": a})["a"]
