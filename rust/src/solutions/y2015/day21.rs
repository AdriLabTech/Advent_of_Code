//! Advent of Code 2015 - Día 21
use crate::aoc::{ints, Answer};

// (coste, daño, armadura) de la tienda
const ARMAS: [(i64, i64, i64); 5] = [(8, 4, 0), (10, 5, 0), (25, 6, 0), (40, 7, 0), (74, 8, 0)];
const ARMADURAS: [(i64, i64, i64); 6] = [(0, 0, 0), (13, 0, 1), (31, 0, 2), (53, 0, 3), (75, 0, 4), (102, 0, 5)]; // la primera = sin armadura
const ANILLOS: [(i64, i64, i64); 6] = [(25, 1, 0), (50, 2, 0), (100, 3, 0), (20, 0, 1), (40, 0, 2), (80, 0, 3)];

/// Gana quien tarda menos turnos en matar al otro (el jugador pega primero, así que gana en un empate).
fn gana_jugador(vida: i64, dano: i64, armadura: i64, jefe: &[i64]) -> bool {
    let turnos_jugador = (jefe[0] + (dano - jefe[2]).max(1) - 1) / (dano - jefe[2]).max(1);
    let turnos_jefe = (vida + (jefe[1] - armadura).max(1) - 1) / (jefe[1] - armadura).max(1);
    turnos_jugador <= turnos_jefe
}

/// (coste, daño, armadura) de cada compra posible: 1 arma, 0-1 armadura y 0-2 anillos.
fn equipamientos() -> Vec<(i64, i64, i64)> {
    let mut v = Vec::new();
    for arma in ARMAS {
        for armadura in ARMADURAS {
            // anillos: ninguno, uno, o dos distintos
            let mut opciones: Vec<Vec<(i64, i64, i64)>> = vec![vec![]];
            for i in 0..ANILLOS.len() {
                opciones.push(vec![ANILLOS[i]]);
                for j in i + 1..ANILLOS.len() {
                    opciones.push(vec![ANILLOS[i], ANILLOS[j]]);
                }
            }
            for anillos in opciones {
                let mut total = (arma.0 + armadura.0, arma.1 + armadura.1, arma.2 + armadura.2);
                for a in anillos {
                    total = (total.0 + a.0, total.1 + a.1, total.2 + a.2);
                }
                v.push(total);
            }
        }
    }
    v
}

pub fn part1(input: &str) -> Answer {
    let jefe = ints(input);
    Some(equipamientos().into_iter().filter(|&(_, d, a)| gana_jugador(100, d, a, &jefe)).map(|e| e.0).min()?.to_string())
}

pub fn part2(input: &str) -> Answer {
    let jefe = ints(input);
    Some(equipamientos().into_iter().filter(|&(_, d, a)| !gana_jugador(100, d, a, &jefe)).map(|e| e.0).max()?.to_string())
}
