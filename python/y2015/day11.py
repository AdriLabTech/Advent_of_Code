"""Advent of Code 2015 - Día 11"""
import re

PROHIBIDAS = "iol"


def incrementar(clave: str) -> str:
    """Suma uno como si fuera un número en base 26 (z pasa a a y acarrea). Salta de golpe las que tienen i, o o l."""
    letras = list(clave)
    for i, c in enumerate(letras):  # si ya hay una letra prohibida, todo lo que va detrás se pone a 'a'
        if c in PROHIBIDAS:
            letras[i] = chr(ord(c) + 1)
            letras[i + 1 :] = "a" * (len(letras) - i - 1)
            return "".join(letras)
    i = len(letras) - 1
    while i >= 0:
        if letras[i] == "z":
            letras[i] = "a"
            i -= 1
        else:
            letras[i] = chr(ord(letras[i]) + 1)
            break
    return "".join(letras)


def es_valida(clave: str) -> bool:
    escalera = any(ord(a) + 1 == ord(b) and ord(b) + 1 == ord(c) for a, b, c in zip(clave, clave[1:], clave[2:]))
    sin_prohibidas = not any(c in clave for c in PROHIBIDAS)
    dos_parejas = len(set(re.findall(r"(.)\1", clave))) >= 2  # dos letras distintas dobles (no se solapan)
    return escalera and sin_prohibidas and dos_parejas


def siguiente_clave(clave: str) -> str:
    clave = incrementar(clave)
    while not es_valida(clave):
        clave = incrementar(clave)
    return clave


def part1(lines: list[str]):
    return siguiente_clave(lines[0].strip())


def part2(lines: list[str]):
    return siguiente_clave(part1(lines))
