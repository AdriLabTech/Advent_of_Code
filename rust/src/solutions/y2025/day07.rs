//! Advent of Code 2025 - Día 7
use crate::aoc::Answer;
use std::collections::BTreeSet;

fn leer(input: &str) -> (Vec<&[u8]>, usize, usize) {
    let mapa: Vec<&[u8]> = input.lines().filter(|l| !l.is_empty()).map(str::as_bytes).collect();
    let (sy, sx) = mapa.iter().enumerate().find_map(|(y, f)| f.iter().position(|&c| c == b'S').map(|x| (y, x))).expect("no hay S");
    (mapa, sy, sx)
}

pub fn part1(input: &str) -> Answer {
    let (mapa, sy, sx) = leer(input);
    let ancho = mapa[0].len();
    let (mut rayos, mut divisiones) = (BTreeSet::from([sx]), 0);
    for y in sy..mapa.len() - 1 {
        // el rayo baja fila a fila
        let mut siguiente = BTreeSet::new();
        for &x in &rayos {
            if mapa[y + 1][x] == b'^' {
                // divisor: sale por los dos lados
                divisiones += 1;
                if x > 0 {
                    siguiente.insert(x - 1);
                }
                if x + 1 < ancho {
                    siguiente.insert(x + 1);
                }
            } else {
                siguiente.insert(x);
            }
        }
        rayos = siguiente;
    }
    Some(divisiones.to_string())
}

pub fn part2(input: &str) -> Answer {
    let (mapa, sy, sx) = leer(input);
    let ancho = mapa[0].len();
    // caminos[x]: líneas temporales que salen por abajo partiendo de (x, y); se rellena de abajo arriba
    let mut caminos = vec![1u128; ancho];
    for y in (sy..mapa.len() - 1).rev() {
        caminos = (0..ancho)
            .map(|x| {
                if mapa[y + 1][x] == b'^' {
                    (if x > 0 { caminos[x - 1] } else { 0 }) + (if x + 1 < ancho { caminos[x + 1] } else { 0 })
                } else {
                    caminos[x]
                }
            })
            .collect();
    }
    Some(caminos[sx].to_string())
}
