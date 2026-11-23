"""Advent of Code 2025 - Día 5"""


def leer(lines: list[str]) -> tuple[list[tuple[int, int]], list[int]]:
    """Rangos frescos 'a-b', línea en blanco y luego los IDs disponibles."""
    rangos, ids, en_rangos = [], [], True
    for line in lines:
        if not line.strip():
            en_rangos = False
        elif en_rangos:
            a, b = line.split("-")
            rangos.append((int(a), int(b)))
        else:
            ids.append(int(line))
    return rangos, ids


def part1(lines: list[str]):
    rangos, ids = leer(lines)
    return sum(any(a <= i <= b for a, b in rangos) for i in ids)


def part2(lines: list[str]):
    # unión de rangos: se ordenan y se fusionan los que se solapan o se tocan; luego se suman sus longitudes
    total, hasta = 0, -1
    for a, b in sorted(leer(lines)[0]):
        if b > hasta:
            total += b - max(a, hasta + 1) + 1
            hasta = b
    return total
