//! Advent of Code 2015 - Día 3
use crate::aoc::Answer;
use std::collections::HashSet;

/// Los repartidores se turnan: el movimiento i lo hace el repartidor i % repartidores.
fn casas_visitadas(ruta: &str, repartidores: usize) -> usize {
    let mut posiciones = vec![(0i32, 0i32); repartidores];
    let mut visitadas = HashSet::from([(0, 0)]);
    for (i, c) in ruta.chars().enumerate() {
        let (dx, dy) = match c {
            '^' => (0, 1),
            'v' => (0, -1),
            '>' => (1, 0),
            '<' => (-1, 0),
            _ => continue,
        };
        let p = &mut posiciones[i % repartidores];
        *p = (p.0 + dx, p.1 + dy);
        visitadas.insert(*p);
    }
    visitadas.len()
}

pub fn part1(input: &str) -> Answer {
    Some(casas_visitadas(input.lines().next()?, 1).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(casas_visitadas(input.lines().next()?, 2).to_string())
}
