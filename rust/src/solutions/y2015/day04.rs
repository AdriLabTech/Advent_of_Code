//! Advent of Code 2015 - Día 4 (el input es la clave secreta: una sola línea de texto)
use crate::aoc::Answer;
use crate::md5::md5;

/// ¿El hash empieza por `ceros` dígitos hexadecimales a cero?
fn empieza_por_ceros(hash: &[u8; 16], ceros: usize) -> bool {
    (0..ceros).all(|i| (if i % 2 == 0 { hash[i / 2] >> 4 } else { hash[i / 2] & 0x0f }) == 0)
}

fn primer_numero(clave: &str, ceros: usize) -> u64 {
    (1u64..).find(|n| empieza_por_ceros(&md5(format!("{clave}{n}").as_bytes()), ceros)).unwrap()
}

pub fn part1(input: &str) -> Answer {
    Some(primer_numero(input.lines().next()?.trim(), 5).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(primer_numero(input.lines().next()?.trim(), 6).to_string())
}
