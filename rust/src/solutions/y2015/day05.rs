//! Advent of Code 2015 - Día 5
use crate::aoc::Answer;

fn es_buena_v1(s: &str) -> bool {
    let b = s.as_bytes();
    let vocales = b.iter().filter(|c| b"aeiou".contains(c)).count() >= 3;
    let doble = b.windows(2).any(|p| p[0] == p[1]);
    let prohibida = ["ab", "cd", "pq", "xy"].iter().any(|p| s.contains(p));
    vocales && doble && !prohibida
}

fn es_buena_v2(s: &str) -> bool {
    let b = s.as_bytes();
    // un par de letras que reaparece más adelante sin solaparse
    let par_repetido = (0..b.len().saturating_sub(1)).any(|i| b[i + 2..].windows(2).any(|p| p == &b[i..i + 2]));
    // una letra que se repite con otra en medio (xyx)
    let letra_entre = b.windows(3).any(|t| t[0] == t[2]);
    par_repetido && letra_entre
}

pub fn part1(input: &str) -> Answer {
    Some(input.lines().filter(|l| es_buena_v1(l)).count().to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(input.lines().filter(|l| es_buena_v2(l)).count().to_string())
}
