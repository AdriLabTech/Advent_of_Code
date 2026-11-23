//! Advent of Code 2025 - Día 1
use crate::aoc::Answer;

const DIAL: i64 = 100; // posiciones del dial (0..99)
const START: i64 = 50; // posición inicial

/// Cada línea (L68, R48...) como desplazamiento con signo: L = negativo, R = positivo.
fn rotations(input: &str) -> impl Iterator<Item = i64> + '_ {
    input.lines().filter(|l| !l.trim().is_empty()).map(|l| {
        let n: i64 = l[1..].trim().parse().expect("distancia no numérica");
        if l.starts_with('L') { -n } else { n }
    })
}

pub fn part1(input: &str) -> Answer {
    let mut pos: i64 = START;
    let mut zeros: u32 = 0;
    for delta in rotations(input) {
        pos = (pos + delta).rem_euclid(DIAL); // rem_euclid siempre da resultado >= 0
        zeros += (pos == 0) as u32;
    }
    Some(zeros.to_string())
}

pub fn part2(input: &str) -> Answer {
    let mut pos: i64 = START;
    let mut zeros: i64 = 0;
    for delta in rotations(input) {
        // Girar a la izquierda equivale a girar a la derecha desde la posición "espejo" (DIAL - pos).
        // Así solo hay que contar cuántas veces se cruza un múltiplo de 100 hacia delante.
        let start: i64 = if delta > 0 { pos } else { (DIAL - pos) % DIAL };
        zeros += (start + delta.abs()) / DIAL;
        pos = (pos + delta).rem_euclid(DIAL);
    }
    Some(zeros.to_string())
}
