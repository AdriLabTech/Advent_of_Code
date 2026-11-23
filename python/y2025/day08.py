"""Advent of Code 2025 - Día 8"""
from math import prod

CONEXIONES = 1000  # pares más cercanos que se conectan en la parte 1
CONEXIONES_EJEMPLO = 10  # el ejemplo del enunciado (20 cajas) conecta solo 10


def leer(lines: list[str]) -> list[tuple[int, ...]]:
    return [tuple(int(v) for v in line.split(",")) for line in lines if line.strip()]


def conectar(cajas: list[tuple[int, ...]], limite_pares: int | None = None):
    """Recorre los pares por distancia creciente (Kruskal) y une los circuitos de cada par.

    Se detiene tras `limite_pares` pares (cuenten o no como unión) o al quedar un solo circuito.
    Devuelve (tamaños de los circuitos, último par que unió dos circuitos distintos).
    """
    n = len(cajas)
    pares = sorted(
        (sum((a - b) ** 2 for a, b in zip(cajas[i], cajas[j])), i, j) for i in range(n) for j in range(i + 1, n)
    )
    padre, tamano = list(range(n)), [1] * n

    def raiz(i: int) -> int:
        while padre[i] != i:
            padre[i] = padre[padre[i]]
            i = padre[i]
        return i

    circuitos, ultimo = n, None
    for visitados, (_, i, j) in enumerate(pares):
        if visitados == limite_pares or circuitos == 1:
            break
        ri, rj = raiz(i), raiz(j)
        if ri != rj:  # si ya estaban en el mismo circuito no pasa nada
            if tamano[ri] < tamano[rj]:
                ri, rj = rj, ri
            padre[rj] = ri
            tamano[ri] += tamano[rj]
            circuitos -= 1
            ultimo = (i, j)
    return [tamano[r] for r in range(n) if padre[r] == r], ultimo


def part1(lines: list[str]):
    cajas = leer(lines)
    tamanos, _ = conectar(cajas, CONEXIONES_EJEMPLO if len(cajas) <= 20 else CONEXIONES)
    return prod(sorted(tamanos, reverse=True)[:3])


def part2(lines: list[str]):
    cajas = leer(lines)
    _, (i, j) = conectar(cajas)  # la última unión es la que deja un solo circuito
    return cajas[i][0] * cajas[j][0]
