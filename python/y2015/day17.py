"""Advent of Code 2015 - Día 17"""

LITROS = 150
LITROS_EJEMPLO = 25  # el ejemplo del enunciado (5 contenedores) guarda 25 litros


def formas_por_cantidad(lines: list[str]) -> dict[int, int]:
    """formas[n] = de cuántas maneras se llenan exactamente los litros con n contenedores (programación dinámica)."""
    contenedores = [int(l) for l in lines if l.strip()]
    litros = LITROS_EJEMPLO if len(contenedores) <= 5 else LITROS
    # tabla[n][s]: subconjuntos de n contenedores que suman s litros
    tabla = [[0] * (litros + 1) for _ in range(len(contenedores) + 1)]
    tabla[0][0] = 1
    for c in contenedores:
        for n in range(len(contenedores) - 1, -1, -1):
            for s in range(litros - c, -1, -1):
                tabla[n + 1][s + c] += tabla[n][s]
    return {n: fila[litros] for n, fila in enumerate(tabla) if fila[litros]}


def part1(lines: list[str]):
    return sum(formas_por_cantidad(lines).values())


def part2(lines: list[str]):
    formas = formas_por_cantidad(lines)
    return formas[min(formas)]  # formas con el menor número posible de contenedores
