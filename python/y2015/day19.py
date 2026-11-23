"""Advent of Code 2015 - Día 19"""
import re


def leer(lines: list[str]) -> tuple[list[tuple[str, str]], str]:
    """Reemplazos 'X => Y', una línea en blanco y la molécula."""
    reemplazos = [tuple(l.split(" => ")) for l in lines if " => " in l]
    molecula = next(l.strip() for l in reversed(lines) if l.strip() and " => " not in l)
    return reemplazos, molecula  # type: ignore[return-value]


def part1(lines: list[str]):
    reemplazos, molecula = leer(lines)
    resultados = set()
    for origen, destino in reemplazos:
        for m in re.finditer(re.escape(origen), molecula):  # cada aparición del origen es un reemplazo posible
            resultados.add(molecula[: m.start()] + destino + molecula[m.end() :])
    return len(resultados)


def pasos_busqueda(reemplazos: list[tuple[str, str]], molecula: str) -> int:
    """Pasos mínimos de 'e' a la molécula: búsqueda en anchura hacia atrás (de la molécula a 'e'). Solo sirve para moléculas cortas."""
    actual, pasos = {molecula}, 0
    while "e" not in actual:
        pasos += 1
        siguiente = set()
        for m in actual:
            for origen, destino in reemplazos:
                for hit in re.finditer(re.escape(destino), m):
                    nueva = m[: hit.start()] + origen + m[hit.end() :]
                    if origen != "e" or nueva == "e":  # 'e' solo vale como paso final
                        siguiente.add(nueva)
        actual = siguiente
    return pasos


def part2(lines: list[str]):
    reemplazos, molecula = leer(lines)
    if "Rn" not in molecula:
        return pasos_busqueda(reemplazos, molecula)
    # Molécula real: cada reemplazo suma un elemento, salvo los de la forma X => X Rn ... Ar (que añaden Rn y Ar)
    # y los que llevan Y (cada Y añade además una coma y otro elemento). Por eso los pasos son:
    # elementos - (Rn + Ar) - 2 * Y - 1
    elementos = len(re.findall(r"[A-Z][a-z]?", molecula))
    return elementos - molecula.count("Rn") - molecula.count("Ar") - 2 * molecula.count("Y") - 1
