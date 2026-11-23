//! Advent of Code 2015 - Día 22
use crate::aoc::{ints, Answer};
use std::cmp::Reverse;
use std::collections::{BinaryHeap, HashSet};

// (coste, daño, curación, duración del efecto); el orden es Misil, Drenaje, Escudo, Veneno, Recarga
const HECHIZOS: [(i64, i64, i64, i64); 5] = [(53, 4, 0, 0), (73, 2, 2, 0), (113, 0, 0, 6), (173, 0, 0, 6), (229, 0, 0, 5)];

/// Estado del combate: (maná gastado, vida jugador, maná, vida jefe, escudo, veneno, recarga)
type Estado = (i64, i64, i64, i64, i64, i64, i64);

/// Aplica los efectos activos al comienzo de un turno. Devuelve (vida jefe, maná, armadura, escudo, veneno, recarga).
fn efectos(vida_jefe: i64, mana: i64, escudo: i64, veneno: i64, recarga: i64) -> (i64, i64, i64, i64, i64, i64) {
    let armadura = if escudo > 0 { 7 } else { 0 };
    let vida_jefe = vida_jefe - if veneno > 0 { 3 } else { 0 };
    let mana = mana + if recarga > 0 { 101 } else { 0 };
    (vida_jefe, mana, armadura, (escudo - 1).max(0), (veneno - 1).max(0), (recarga - 1).max(0))
}

/// Búsqueda de Dijkstra por maná gastado sobre los estados del combate. None si no se puede ganar.
fn minimo_mana(vida_jefe: i64, dano_jefe: i64, vida: i64, mana: i64, dificil: bool) -> Option<i64> {
    let mut cola: BinaryHeap<Reverse<Estado>> = BinaryHeap::new();
    cola.push(Reverse((0, vida, mana, vida_jefe, 0, 0, 0)));
    let mut vistos = HashSet::new();
    while let Some(Reverse((gastado, mut vida, mana, vida_jefe, escudo, veneno, recarga))) = cola.pop() {
        if vida_jefe <= 0 {
            return Some(gastado); // estado ganador: como se saca de la cola por maná creciente, es el mínimo
        }
        if !vistos.insert((vida, mana, vida_jefe, escudo, veneno, recarga)) {
            continue;
        }
        // --- turno del jugador ---
        if dificil {
            vida -= 1;
            if vida <= 0 {
                continue;
            }
        }
        let (vida_jefe, mana, _, escudo, veneno, recarga) = efectos(vida_jefe, mana, escudo, veneno, recarga);
        if vida_jefe <= 0 {
            return Some(gastado);
        }
        for (indice, &(coste, dano, cura, duracion)) in HECHIZOS.iter().enumerate() {
            let activo = [escudo, veneno, recarga];
            if coste > mana || (indice >= 2 && activo[indice - 2] > 0) {
                continue;
            }
            let (m, vj, mut v) = (mana - coste, vida_jefe - dano, vida + cura);
            let (mut e, mut p, mut r) = (escudo, veneno, recarga);
            match indice {
                2 => e = duracion,
                3 => p = duracion,
                4 => r = duracion,
                _ => {}
            }
            if vj <= 0 {
                cola.push(Reverse((gastado + coste, v, m, vj, e, p, r))); // gana nada más lanzarlo
                continue;
            }
            // --- turno del jefe ---
            let (vj, m, armadura, e, p, r) = efectos(vj, m, e, p, r);
            if vj <= 0 {
                cola.push(Reverse((gastado + coste, v, m, vj, e, p, r)));
                continue;
            }
            v -= (dano_jefe - armadura).max(1);
            if v > 0 {
                cola.push(Reverse((gastado + coste, v, m, vj, e, p, r)));
            }
        }
    }
    None
}

pub fn part1(input: &str) -> Answer {
    let n = ints(input);
    Some(minimo_mana(n[0], n[1], 50, 500, false)?.to_string())
}

pub fn part2(input: &str) -> Answer {
    let n = ints(input);
    Some(minimo_mana(n[0], n[1], 50, 500, true)?.to_string())
}
