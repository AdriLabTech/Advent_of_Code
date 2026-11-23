//! Advent of Code 2025 - Día 4
use crate::aoc::Answer;
use std::collections::HashSet;

type Rollo = (i32, i32);

const VECINOS: [(i32, i32); 8] = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)];

fn leer_rollos(input: &str) -> HashSet<Rollo> {
    let mut rollos = HashSet::new();
    for (r, line) in input.lines().enumerate() {
        for (c, ch) in line.chars().enumerate() {
            if ch == '@' {
                rollos.insert((r as i32, c as i32));
            }
        }
    }
    rollos
}

/// Rollos con menos de 4 rollos vecinos.
fn accesibles(rollos: &HashSet<Rollo>) -> Vec<Rollo> {
    rollos
        .iter()
        .filter(|&&(r, c)| VECINOS.iter().filter(|&&(dr, dc)| rollos.contains(&(r + dr, c + dc))).count() < 4)
        .copied()
        .collect()
}

pub fn part1(input: &str) -> Answer {
    Some(accesibles(&leer_rollos(input)).len().to_string())
}

pub fn part2(input: &str) -> Answer {
    let mut rollos = leer_rollos(input);
    let mut quitados = 0;
    loop {
        let retirar = accesibles(&rollos); // se repite hasta que no quede ninguno accesible
        if retirar.is_empty() {
            break;
        }
        quitados += retirar.len();
        for r in retirar {
            rollos.remove(&r);
        }
    }
    Some(quitados.to_string())
}
