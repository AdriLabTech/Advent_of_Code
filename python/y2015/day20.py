"""Advent of Code 2015 - Día 20 (el input es un número en una línea)"""


def regalos(limite: int, por_elfo: int, casas_por_elfo: int | None) -> list[int]:
    """regalos[c] = presentes que recibe la casa c (criba: cada elfo recorre sus casas) hasta la casa `limite`."""
    casas = [0] * (limite + 1)
    for elfo in range(1, limite + 1):
        ultima = limite if casas_por_elfo is None else min(limite, elfo * casas_por_elfo)
        for casa in range(elfo, ultima + 1, elfo):
            casas[casa] += por_elfo * elfo
    return casas


def primera_casa(objetivo: int, por_elfo: int, casas_por_elfo: int | None) -> int:
    limite = 1 << 14
    while True:  # si no aparece, se duplica el rango y se vuelve a cribar
        for casa, total in enumerate(regalos(limite, por_elfo, casas_por_elfo)):
            if total >= objetivo:
                return casa
        limite *= 2


def part1(lines: list[str]):
    return primera_casa(int(lines[0]), 10, None)


def part2(lines: list[str]):
    return primera_casa(int(lines[0]), 11, 50)  # cada elfo reparte 11 veces su número y solo a 50 casas
