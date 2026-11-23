//! Advent of Code 2025 - Día 3
use crate::aoc::Answer;

/// Número más grande que se forma encendiendo `cuantas` baterías sin cambiar su orden (voraz).
fn mayor_joltaje(banco: &str, cuantas: usize) -> u64 {
    let baterias = banco.as_bytes();
    let mut elegidas: Vec<u8> = Vec::new();
    for (i, &bateria) in baterias.iter().enumerate() {
        // una elegida peor que la actual se descarta mientras queden baterías de sobra para completar el número
        while elegidas.last().is_some_and(|&ultima| ultima < bateria) && elegidas.len() + baterias.len() - i > cuantas {
            elegidas.pop();
        }
        if elegidas.len() < cuantas {
            elegidas.push(bateria);
        }
    }
    elegidas.iter().fold(0, |numero, &d| numero * 10 + u64::from(d - b'0'))
}

fn total(input: &str, cuantas: usize) -> Answer {
    let suma: u64 = input.lines().map(str::trim).filter(|l| !l.is_empty()).map(|l| mayor_joltaje(l, cuantas)).sum();
    Some(suma.to_string())
}

pub fn part1(input: &str) -> Answer {
    total(input, 2)
}

pub fn part2(input: &str) -> Answer {
    total(input, 12)
}
