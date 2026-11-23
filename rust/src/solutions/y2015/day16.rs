//! Advent of Code 2015 - Día 16
use crate::aoc::Answer;
use std::cmp::Ordering;
use std::collections::HashMap;

const HUELLA: [(&str, i32); 10] = [
    ("children", 3), ("cats", 7), ("samoyeds", 2), ("pomeranians", 3), ("akitas", 0),
    ("vizslas", 0), ("goldfish", 5), ("trees", 3), ("cars", 2), ("perfumes", 1),
];

/// (número, {compuesto: cantidad}) de cada línea 'Sue 1: goldfish: 6, trees: 9, ...'.
fn tias(input: &str) -> Vec<(u32, HashMap<&str, i32>)> {
    input.lines().filter(|l| !l.trim().is_empty()).map(|l| {
        let (cabecera, resto) = l.split_once(':').unwrap();
        let numero = cabecera.trim_start_matches("Sue ").trim().parse().unwrap();
        let recuerdos = resto.split(',').map(|p| {
            let (k, v) = p.split_once(':').unwrap();
            (k.trim(), v.trim().parse().unwrap())
        }).collect();
        (numero, recuerdos)
    }).collect()
}

/// La tía cuyos recuerdos cumplen `ordenacion(compuesto)` (el orden que debe tener su valor respecto a la huella).
fn buscar(input: &str, ordenacion: impl Fn(&str) -> Ordering) -> Answer {
    let huella: HashMap<&str, i32> = HUELLA.into_iter().collect();
    tias(input).into_iter().find(|(_, r)| r.iter().all(|(k, v)| v.cmp(&huella[k]) == ordenacion(k))).map(|(n, _)| n.to_string())
}

pub fn part1(input: &str) -> Answer {
    buscar(input, |_| Ordering::Equal)
}

pub fn part2(input: &str) -> Answer {
    // cats y trees: mayor que la huella; pomeranians y goldfish: menor
    buscar(input, |k| match k {
        "cats" | "trees" => Ordering::Greater,
        "pomeranians" | "goldfish" => Ordering::Less,
        _ => Ordering::Equal,
    })
}
