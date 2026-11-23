"""Advent of Code 2015 - Día 22"""
import heapq
from aoc import ints

# (nombre, coste, daño, curación, duración del efecto)
HECHIZOS = [("Misil", 53, 4, 0, 0), ("Drenaje", 73, 2, 2, 0), ("Escudo", 113, 0, 0, 6), ("Veneno", 173, 0, 0, 6), ("Recarga", 229, 0, 0, 5)]


def efectos(vida_jefe: int, mana: int, escudo: int, veneno: int, recarga: int):
    """Aplica los efectos activos al comienzo de un turno. Devuelve (vida_jefe, mana, armadura, temporizadores...)."""
    armadura = 7 if escudo else 0
    if veneno:
        vida_jefe -= 3
    if recarga:
        mana += 101
    return vida_jefe, mana, armadura, max(0, escudo - 1), max(0, veneno - 1), max(0, recarga - 1)


def minimo_mana(vida_jefe: int, dano_jefe: int, vida: int = 50, mana: int = 500, dificil: bool = False):
    """Búsqueda de Dijkstra por maná gastado sobre los estados del combate. None si no se puede ganar."""
    # estado: (maná gastado, vida jugador, maná, vida jefe, escudo, veneno, recarga)
    cola = [(0, vida, mana, vida_jefe, 0, 0, 0)]
    vistos = set()
    while cola:
        gastado, vida, mana, vida_jefe, escudo, veneno, recarga = heapq.heappop(cola)
        if vida_jefe <= 0:
            return gastado  # estado ganador: como se saca de la cola por maná creciente, es el mínimo
        if (vida, mana, vida_jefe, escudo, veneno, recarga) in vistos:
            continue
        vistos.add((vida, mana, vida_jefe, escudo, veneno, recarga))
        # --- turno del jugador ---
        if dificil:
            vida -= 1
            if vida <= 0:
                continue
        vida_jefe, mana, _, escudo, veneno, recarga = efectos(vida_jefe, mana, escudo, veneno, recarga)
        if vida_jefe <= 0:
            return gastado
        for nombre, coste, dano, cura, duracion in HECHIZOS:
            if coste > mana or (nombre == "Escudo" and escudo) or (nombre == "Veneno" and veneno) or (nombre == "Recarga" and recarga):
                continue
            m, vj, v = mana - coste, vida_jefe - dano, vida + cura
            e, p, r = escudo, veneno, recarga
            if nombre == "Escudo":
                e = duracion
            elif nombre == "Veneno":
                p = duracion
            elif nombre == "Recarga":
                r = duracion
            if vj <= 0:
                heapq.heappush(cola, (gastado + coste, v, m, vj, e, p, r))  # gana nada más lanzarlo
                continue
            # --- turno del jefe ---
            vj, m, armadura, e, p, r = efectos(vj, m, e, p, r)
            if vj <= 0:
                heapq.heappush(cola, (gastado + coste, v, m, vj, e, p, r))
                continue
            v -= max(1, dano_jefe - armadura)
            if v > 0:
                heapq.heappush(cola, (gastado + coste, v, m, vj, e, p, r))
    return None


def part1(lines: list[str]):
    vida_jefe, dano_jefe = ints(" ".join(lines))
    return minimo_mana(vida_jefe, dano_jefe)


def part2(lines: list[str]):
    vida_jefe, dano_jefe = ints(" ".join(lines))
    return minimo_mana(vida_jefe, dano_jefe, dificil=True)
