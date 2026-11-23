"""Advent of Code 2025 - Día 12"""
from aoc import paragraphs

Celda = tuple[int, int]


def leer(lines: list[str]):
    """Formas ('0:' + filas) y regiones ('AxB: q0 q1 ...')."""
    formas, regiones = {}, []
    for bloque in paragraphs(lines):
        if bloque[0].endswith(":"):
            formas[int(bloque[0][:-1])] = [(r, c) for r, fila in enumerate(bloque[1:]) for c, ch in enumerate(fila) if ch == "#"]
        else:
            for linea in bloque:
                tam, cantidades = linea.split(":")
                ancho, alto = (int(v) for v in tam.split("x"))
                regiones.append((ancho, alto, [int(q) for q in cantidades.split()]))
    return formas, regiones


def orientaciones(forma: list[Celda]) -> list[list[Celda]]:
    """Las rotaciones y reflejos distintos de una forma, normalizados a la esquina superior izquierda."""
    resultado = set()
    celdas = forma
    for _ in range(4):
        celdas = [(c, -r) for r, c in celdas]  # rotar 90°
        for espejo in (celdas, [(r, -c) for r, c in celdas]):
            menor_r, menor_c = min(r for r, _ in espejo), min(c for _, c in espejo)
            resultado.add(tuple(sorted((r - menor_r, c - menor_c) for r, c in espejo)))
    return [list(o) for o in resultado]


def cabe(ancho: int, alto: int, cantidades: list[int], formas_orient: dict[int, list[list[Celda]]], tamanos: dict[int, int]) -> bool:
    piezas = [i for i, q in enumerate(cantidades) for _ in range(q)]
    celdas = sum(tamanos[i] for i in piezas)
    holgura = ancho * alto - celdas
    if holgura < 0:
        return False  # no caben ni sin huecos
    if len(piezas) <= (ancho // 3) * (alto // 3):
        return True  # cada pieza cabe en un cuadrado de 3x3 y hay sitio para todos esos cuadrados

    # búsqueda exacta: se rellena la primera celda libre (por filas) con una pieza o se deja vacía
    libres = [[True] * ancho for _ in range(alto)]
    restantes = list(cantidades)

    def resolver(pos: int, hueco: int) -> bool:
        while pos < ancho * alto and not libres[pos // ancho][pos % ancho]:
            pos += 1
        if pos == ancho * alto:
            return not any(restantes)
        r0, c0 = divmod(pos, ancho)
        for i, q in enumerate(restantes):
            if q == 0:
                continue
            for orient in formas_orient[i]:
                # la primera celda de la forma (por filas) es la que se apoya en la celda libre
                dr, dc = orient[0]
                destino = [(r0 + r - dr, c0 + c - dc) for r, c in orient]
                if all(0 <= r < alto and 0 <= c < ancho and libres[r][c] for r, c in destino):
                    for r, c in destino:
                        libres[r][c] = False
                    restantes[i] -= 1
                    if resolver(pos + 1, hueco):
                        return True
                    restantes[i] += 1
                    for r, c in destino:
                        libres[r][c] = True
        if hueco > 0:  # dejar esta celda vacía
            libres[r0][c0] = False
            if resolver(pos + 1, hueco - 1):
                return True
            libres[r0][c0] = True
        return False

    return resolver(0, holgura)


def part1(lines: list[str]):
    formas, regiones = leer(lines)
    orient = {i: orientaciones(f) for i, f in formas.items()}
    tamanos = {i: len(f) for i, f in formas.items()}
    return sum(cabe(ancho, alto, q, orient, tamanos) for ancho, alto, q in regiones)


def part2(lines: list[str]):
    return None  # pendiente: la parte 2 se desbloquea al completar el resto de días
