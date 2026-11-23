//! Advent of Code 2025 - Día 10
use crate::aoc::Answer;
use std::collections::HashMap;

struct Maquina {
    luces: Vec<bool>,
    botones: Vec<Vec<usize>>,
    contadores: Vec<u32>,
}

/// '[.##.] (3) (1,3) ... {3,5,4}' -> luces objetivo, botones y contadores objetivo.
fn leer(line: &str) -> Maquina {
    let entre = |abre: char, cierra: char, desde: usize| -> Option<(usize, usize)> {
        let a = line[desde..].find(abre)? + desde;
        Some((a, line[a..].find(cierra)? + a))
    };
    let (a, b) = entre('[', ']', 0).expect("sin diagrama");
    let luces = line[a + 1..b].chars().map(|c| c == '#').collect();

    let (llave, fin) = entre('{', '}', 0).expect("sin contadores");
    let contadores = line[llave + 1..fin].split(',').map(|n| n.trim().parse().unwrap()).collect();

    let mut botones = Vec::new();
    let mut pos = b;
    while let Some((p, q)) = entre('(', ')', pos).filter(|&(p, _)| p < llave) {
        botones.push(line[p + 1..q].split(',').filter(|n| !n.trim().is_empty()).map(|n| n.trim().parse().unwrap()).collect());
        pos = q;
    }
    Maquina { luces, botones, contadores }
}

/// Para cada combinación de botones (cada uno 0 o 1 veces): incremento de cada contador -> mínimo de pulsaciones.
fn patrones(botones: &[Vec<usize>], n: usize) -> HashMap<Vec<u32>, u32> {
    let mut mejor: HashMap<Vec<u32>, u32> = HashMap::new();
    for seleccion in 0u32..(1 << botones.len()) {
        let mut incremento = vec![0u32; n];
        for (j, boton) in botones.iter().enumerate() {
            if seleccion >> j & 1 == 1 {
                boton.iter().for_each(|&i| incremento[i] += 1);
            }
        }
        let pulsaciones = seleccion.count_ones();
        let e = mejor.entry(incremento).or_insert(pulsaciones);
        *e = (*e).min(pulsaciones);
    }
    mejor
}

/// Truco de la mitad: tras elegir una combinación con la misma paridad, el resto se pulsa por pares.
fn minimo(actual: &[u32], pats: &HashMap<Vec<u32>, u32>, memo: &mut HashMap<Vec<u32>, u64>) -> u64 {
    if actual.iter().all(|&v| v == 0) {
        return 0;
    }
    if let Some(&m) = memo.get(actual) {
        return m;
    }
    let mut mejor = u64::MAX;
    for (inc, &pulsaciones) in pats {
        if actual.iter().zip(inc).all(|(&c, &p)| p <= c && (c - p) % 2 == 0) {
            let mitad: Vec<u32> = actual.iter().zip(inc).map(|(&c, &p)| (c - p) / 2).collect();
            let sub = minimo(&mitad, pats, memo);
            if sub != u64::MAX {
                mejor = mejor.min(pulsaciones as u64 + 2 * sub);
            }
        }
    }
    memo.insert(actual.to_vec(), mejor);
    mejor
}

pub fn part1(input: &str) -> Answer {
    let mut total = 0u64;
    for line in input.lines().filter(|l| !l.trim().is_empty()) {
        let m = leer(line);
        // solo importa la paridad de cada luz: se busca la combinación con esa paridad y menos pulsaciones
        let minimo = patrones(&m.botones, m.luces.len())
            .into_iter()
            .filter(|(inc, _)| inc.iter().zip(&m.luces).all(|(&v, &luz)| (v % 2 == 1) == luz))
            .map(|(_, p)| p)
            .min()
            .expect("luces imposibles");
        total += minimo as u64;
    }
    Some(total.to_string())
}

pub fn part2(input: &str) -> Answer {
    let mut total = 0u64;
    for line in input.lines().filter(|l| !l.trim().is_empty()) {
        let m = leer(line);
        let pats = patrones(&m.botones, m.contadores.len());
        total += minimo(&m.contadores, &pats, &mut HashMap::new());
    }
    Some(total.to_string())
}
