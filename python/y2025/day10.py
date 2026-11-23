"""Advent of Code 2025 - Día 10"""
import re
from functools import cache
from itertools import product


def leer(line: str):
    """'[.##.] (3) (1,3) ... {3,5,4}' -> (luces objetivo, botones, contadores objetivo)."""
    luces = re.search(r"\[(.*?)\]", line).group(1)
    botones = [[int(n) for n in b.split(",") if n.strip()] for b in re.findall(r"\((.*?)\)", line)]
    contadores = [int(n) for n in re.search(r"\{(.*?)\}", line).group(1).split(",")]
    return luces, botones, contadores


def patrones(botones: list[list[int]], n: int) -> dict[tuple[int, ...], int]:
    """Para cada combinación de botones (cada uno 0 o 1 veces): incremento de cada contador -> mínimo de pulsaciones."""
    mejor: dict[tuple[int, ...], int] = {}
    for seleccion in product((0, 1), repeat=len(botones)):
        incremento = [0] * n
        for pulsado, boton in zip(seleccion, botones):
            if pulsado:
                for i in boton:
                    incremento[i] += 1
        clave = tuple(incremento)
        mejor[clave] = min(mejor.get(clave, len(botones)), sum(seleccion))
    return mejor


def part1(lines: list[str]):
    total = 0
    for line in lines:
        if line.strip():
            luces, botones, _ = leer(line)
            objetivo = tuple(1 if c == "#" else 0 for c in luces)
            # solo importa la paridad de cada luz: se busca la combinación con esa paridad y menos pulsaciones
            total += min(p for inc, p in patrones(botones, len(luces)).items() if tuple(v % 2 for v in inc) == objetivo)
    return total


def part2(lines: list[str]):
    total = 0
    for line in lines:
        if line.strip():
            _, botones, objetivo = leer(line)
            pats = patrones(botones, len(objetivo))

            @cache
            def minimo(actual: tuple[int, ...]) -> float:
                # truco de la mitad: tras elegir una combinación con la misma paridad, el resto se pulsa por pares
                if not any(actual):
                    return 0
                mejor = float("inf")
                for inc, pulsaciones in pats.items():
                    if all(p <= c and (c - p) % 2 == 0 for c, p in zip(actual, inc)):
                        mejor = min(mejor, pulsaciones + 2 * minimo(tuple((c - p) // 2 for c, p in zip(actual, inc))))
                return mejor

            total += minimo(tuple(objetivo))
    return total
