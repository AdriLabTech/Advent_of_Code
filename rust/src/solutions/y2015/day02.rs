//! Advent of Code 2015 - Día 2
use crate::aoc::Answer;

/// Cada línea 'AxBxC' como [a, b, c] con a <= b <= c.
fn cajas(input: &str) -> impl Iterator<Item = [u64; 3]> + '_ {
    input.lines().filter(|l| !l.trim().is_empty()).map(|l| {
        let mut d: Vec<u64> = l.split('x').map(|n| n.trim().parse().expect("medida no numérica")).collect();
        d.sort();
        [d[0], d[1], d[2]]
    })
}

pub fn part1(input: &str) -> Answer {
    // superficie total + el lado más pequeño (a*b) como holgura
    let total: u64 = cajas(input).map(|[a, b, c]| 2 * (a * b + b * c + a * c) + a * b).sum();
    Some(total.to_string())
}

pub fn part2(input: &str) -> Answer {
    // perímetro de la cara más pequeña + volumen
    let total: u64 = cajas(input).map(|[a, b, c]| 2 * (a + b) + a * b * c).sum();
    Some(total.to_string())
}
