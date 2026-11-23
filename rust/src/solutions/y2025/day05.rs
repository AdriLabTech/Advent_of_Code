//! Advent of Code 2025 - Día 5
use crate::aoc::Answer;

/// Rangos frescos 'a-b', línea en blanco y luego los IDs disponibles.
fn leer(input: &str) -> (Vec<(u64, u64)>, Vec<u64>) {
    let (mut rangos, mut ids, mut en_rangos) = (Vec::new(), Vec::new(), true);
    for line in input.lines() {
        if line.trim().is_empty() {
            en_rangos = false;
        } else if en_rangos {
            let (a, b) = line.split_once('-').expect("rango sin guion");
            rangos.push((a.trim().parse().unwrap(), b.trim().parse().unwrap()));
        } else {
            ids.push(line.trim().parse().unwrap());
        }
    }
    (rangos, ids)
}

pub fn part1(input: &str) -> Answer {
    let (rangos, ids) = leer(input);
    Some(ids.iter().filter(|&&i| rangos.iter().any(|&(a, b)| a <= i && i <= b)).count().to_string())
}

pub fn part2(input: &str) -> Answer {
    // unión de rangos: se ordenan y se fusionan los que se solapan o se tocan; luego se suman sus longitudes
    let mut rangos = leer(input).0;
    rangos.sort();
    let (mut total, mut hasta) = (0u64, None::<u64>);
    for (a, b) in rangos {
        if hasta.is_none_or(|h| b > h) {
            let desde = hasta.map_or(a, |h| a.max(h + 1));
            total += b - desde + 1;
            hasta = Some(b);
        }
    }
    Some(total.to_string())
}
