"""Advent of Code 2025 - Día 3"""


def mayor_joltaje(banco: str, cuantas: int) -> int:
    """Número más grande que se forma encendiendo `cuantas` baterías sin cambiar su orden (voraz)."""
    elegidas: list[str] = []
    for i, bateria in enumerate(banco):
        # una elegida peor que la actual se descarta mientras queden baterías de sobra para completar el número
        while elegidas and elegidas[-1] < bateria and len(elegidas) + len(banco) - i > cuantas:
            elegidas.pop()
        if len(elegidas) < cuantas:
            elegidas.append(bateria)
    return int("".join(elegidas))


def part1(lines: list[str]):
    return sum(mayor_joltaje(banco, 2) for banco in lines if banco.strip())


def part2(lines: list[str]):
    return sum(mayor_joltaje(banco, 12) for banco in lines if banco.strip())
