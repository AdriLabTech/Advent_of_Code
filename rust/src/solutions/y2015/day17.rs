//! Advent of Code 2015 - Día 17
use crate::aoc::Answer;

const LITROS: usize = 150;
const LITROS_EJEMPLO: usize = 25; // el ejemplo del enunciado (5 contenedores) guarda 25 litros

/// formas[n] = de cuántas maneras se llenan exactamente los litros con n contenedores (programación dinámica).
fn formas_por_cantidad(input: &str) -> Vec<u64> {
    let contenedores: Vec<usize> = input.lines().filter(|l| !l.trim().is_empty()).map(|l| l.trim().parse().unwrap()).collect();
    let litros = if contenedores.len() <= 5 { LITROS_EJEMPLO } else { LITROS };
    // tabla[n][s]: subconjuntos de n contenedores que suman s litros
    let mut tabla = vec![vec![0u64; litros + 1]; contenedores.len() + 1];
    tabla[0][0] = 1;
    for &c in &contenedores {
        for n in (0..contenedores.len()).rev() {
            for s in (0..=litros.saturating_sub(c)).rev() {
                if s + c <= litros {
                    tabla[n + 1][s + c] += tabla[n][s];
                }
            }
        }
    }
    tabla.iter().map(|fila| fila[litros]).collect()
}

pub fn part1(input: &str) -> Answer {
    Some(formas_por_cantidad(input).iter().sum::<u64>().to_string())
}

pub fn part2(input: &str) -> Answer {
    // formas con el menor número posible de contenedores
    Some(formas_por_cantidad(input).into_iter().find(|&f| f > 0)?.to_string())
}
