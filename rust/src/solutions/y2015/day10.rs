//! Advent of Code 2015 - Día 10
use crate::aoc::Answer;

/// Cada tanda de dígitos iguales se sustituye por (cuántos)(qué dígito).
fn mirar_y_decir(texto: &str, veces: usize) -> usize {
    let mut actual: Vec<u8> = texto.bytes().collect();
    for _ in 0..veces {
        let mut siguiente = Vec::with_capacity(actual.len() * 2);
        let mut i = 0;
        while i < actual.len() {
            let mut j = i;
            while j < actual.len() && actual[j] == actual[i] {
                j += 1;
            }
            siguiente.extend((j - i).to_string().bytes());
            siguiente.push(actual[i]);
            i = j;
        }
        actual = siguiente;
    }
    actual.len()
}

pub fn part1(input: &str) -> Answer {
    Some(mirar_y_decir(input.lines().next()?.trim(), 40).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(mirar_y_decir(input.lines().next()?.trim(), 50).to_string())
}
