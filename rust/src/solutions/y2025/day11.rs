//! Advent of Code 2025 - Día 11
use crate::aoc::Answer;
use std::collections::HashMap;

const OBLIGATORIOS: [&str; 2] = ["dac", "fft"];

type Grafo<'a> = HashMap<&'a str, Vec<&'a str>>;

fn leer(input: &str) -> Grafo<'_> {
    input
        .lines()
        .filter(|l| !l.trim().is_empty())
        .map(|l| {
            let (nombre, salidas) = l.split_once(':').unwrap_or((l, ""));
            (nombre.trim(), salidas.split_whitespace().collect())
        })
        .collect()
}

fn caminos<'a>(nodo: &'a str, grafo: &Grafo<'a>, memo: &mut HashMap<&'a str, u64>) -> u64 {
    if nodo == "out" {
        return 1;
    }
    if let Some(&m) = memo.get(nodo) {
        return m;
    }
    let total = grafo.get(nodo).into_iter().flatten().map(|s| caminos(s, grafo, memo)).sum();
    memo.insert(nodo, total);
    total
}

/// `pendientes` es una máscara de bits con los obligatorios que aún no se han visitado.
fn caminos_obligatorios<'a>(nodo: &'a str, pendientes: u8, grafo: &Grafo<'a>, memo: &mut HashMap<(&'a str, u8), u64>) -> u64 {
    if nodo == "out" {
        return (pendientes == 0) as u64; // solo vale si pasó por todos los obligatorios
    }
    if let Some(&m) = memo.get(&(nodo, pendientes)) {
        return m;
    }
    let pendientes_ahora = OBLIGATORIOS.iter().position(|&o| o == nodo).map_or(pendientes, |i| pendientes & !(1 << i));
    let total = grafo.get(nodo).into_iter().flatten().map(|s| caminos_obligatorios(s, pendientes_ahora, grafo, memo)).sum();
    memo.insert((nodo, pendientes), total);
    total
}

pub fn part1(input: &str) -> Answer {
    Some(caminos("you", &leer(input), &mut HashMap::new()).to_string())
}

pub fn part2(input: &str) -> Answer {
    let todos = (1u8 << OBLIGATORIOS.len()) - 1;
    Some(caminos_obligatorios("svr", todos, &leer(input), &mut HashMap::new()).to_string())
}
