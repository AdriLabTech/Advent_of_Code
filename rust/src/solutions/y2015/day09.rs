//! Advent of Code 2015 - Día 9
use crate::aoc::Answer;
use std::collections::HashMap;

/// (ruta más corta, ruta más larga) que visitan todas las ciudades exactamente una vez (hay pocas: se prueban todas).
fn rutas(input: &str) -> (u32, u32) {
    let mut ids: HashMap<&str, usize> = HashMap::new();
    let mut tramos = Vec::new();
    for l in input.lines().filter(|l| !l.trim().is_empty()) {
        let (ciudades, numero) = l.split_once(" = ").unwrap();
        let (a, b) = ciudades.split_once(" to ").unwrap();
        let n = ids.len();
        let a = *ids.entry(a).or_insert(n);
        let n = ids.len();
        let b = *ids.entry(b).or_insert(n);
        tramos.push((a, b, numero.trim().parse::<u32>().unwrap()));
    }
    let n = ids.len();
    let mut d = vec![vec![0u32; n]; n];
    for (a, b, v) in tramos {
        d[a][b] = v;
        d[b][a] = v;
    }

    fn recorrer(actual: usize, visitadas: u32, recorrido: u32, d: &[Vec<u32>], mejor: &mut (u32, u32)) {
        if visitadas.count_ones() as usize == d.len() {
            mejor.0 = mejor.0.min(recorrido);
            mejor.1 = mejor.1.max(recorrido);
            return;
        }
        for siguiente in 0..d.len() {
            if visitadas >> siguiente & 1 == 0 {
                recorrer(siguiente, visitadas | 1 << siguiente, recorrido + d[actual][siguiente], d, mejor);
            }
        }
    }
    let mut mejor = (u32::MAX, 0);
    for inicio in 0..n {
        recorrer(inicio, 1 << inicio, 0, &d, &mut mejor);
    }
    mejor
}

pub fn part1(input: &str) -> Answer {
    Some(rutas(input).0.to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(rutas(input).1.to_string())
}
