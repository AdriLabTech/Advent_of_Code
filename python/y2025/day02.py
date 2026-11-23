"""Advent of Code 2025 - Día 2"""


def rangos(lines: list[str]) -> list[tuple[int, int]]:
    """Líneas 'a-b,c-d,...' como lista de (a, b)."""
    return [
        (int(a), int(b))
        for line in lines
        for r in line.split(",")
        if r.strip()
        for a, b in [r.strip().split("-")]
    ]


def suma_con_periodo(a: int, b: int, largo: int, periodo: int) -> int:
    """Suma de los números de `largo` dígitos en [a, b] formados repitiendo un bloque de `periodo` dígitos."""
    a, b = max(a, 10 ** (largo - 1)), min(b, 10**largo - 1)
    m = (10**largo - 1) // (10**periodo - 1)  # n = x * m con x de `periodo` dígitos
    menor = max(10 ** (periodo - 1), -(-a // m))
    mayor = min(10**periodo - 1, b // m)
    return m * (menor + mayor) * (mayor - menor + 1) // 2 if menor <= mayor else 0


def part1(lines: list[str]):
    # ID inválido = un bloque repetido exactamente dos veces: periodo = mitad de los dígitos
    return sum(
        suma_con_periodo(a, b, largo, largo // 2)
        for a, b in rangos(lines)
        for largo in range(2, len(str(b)) + 1, 2)
    )


def part2(lines: list[str]):
    # ahora vale cualquier número de repeticiones (>= 2): un periodo p < largo que divida al largo.
    # Un mismo número puede tener varios periodos (111111 -> 1, 2 y 3), así que se suma por periodo
    # mínimo exacto: g[p] = (números con periodo p) - (los que ya tienen un periodo menor que divide a p)
    total = 0
    for a, b in rangos(lines):
        for largo in range(2, len(str(b)) + 1):
            g: dict[int, int] = {}
            for p in range(1, largo):
                if largo % p == 0:
                    g[p] = suma_con_periodo(a, b, largo, p) - sum(g[d] for d in g if p % d == 0)
            total += sum(g.values())
    return total
