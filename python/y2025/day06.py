"""Advent of Code 2025 - Día 6"""
import re
from collections import defaultdict
from math import prod


def part1(lines: list[str]):
    # cada columna de la hoja: varios números y, al final, el operador
    columnas = defaultdict(list)
    for line in lines:
        if line.strip():
            patron = r"[*+]" if "*" in line else r"\d+"
            for i, token in enumerate(re.findall(patron, line)):
                columnas[i].append(token)

    total = 0
    for *numeros, operador in columnas.values():
        valores = [int(n) for n in numeros]
        total += sum(valores) if operador == "+" else prod(valores) if operador == "*" else valores[0]
    return total


def part2(lines: list[str]):
    # se lee carácter a carácter: cada columna de la hoja es un número y el operador marca el grupo
    filas = [line for line in lines if line.strip()]
    total = acumulado = 0
    en_grupo = multiplica = False
    for i in range(max(map(len, filas))):
        columna = [fila[i] for fila in filas if i < len(fila)]
        if columna[-1] in "+*":  # empieza un grupo nuevo
            multiplica, en_grupo, acumulado = columna[-1] == "*", True, None
        texto = "".join(columna[:-1]).strip()
        if not texto:  # columna vacía = fin del grupo
            if en_grupo:
                total += acumulado or 0
            en_grupo = False
            continue
        valor = int(texto)
        acumulado = valor if acumulado is None else acumulado * valor if multiplica else acumulado + valor
    if en_grupo:  # el último grupo no tiene columna vacía detrás
        total += acumulado or 0
    return total
