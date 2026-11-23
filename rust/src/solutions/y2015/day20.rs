//! Advent of Code 2015 - Día 20 (el input es un número en una línea)
use crate::aoc::Answer;

/// regalos[c] = presentes que recibe la casa c (criba: cada elfo recorre sus casas) hasta la casa `limite`.
fn regalos(limite: usize, por_elfo: usize, casas_por_elfo: Option<usize>) -> Vec<usize> {
    let mut casas = vec![0; limite + 1];
    for elfo in 1..=limite {
        let ultima = casas_por_elfo.map_or(limite, |n| limite.min(elfo * n));
        for casa in (elfo..=ultima).step_by(elfo) {
            casas[casa] += por_elfo * elfo;
        }
    }
    casas
}

fn primera_casa(objetivo: usize, por_elfo: usize, casas_por_elfo: Option<usize>) -> usize {
    let mut limite = 1 << 14;
    loop {
        // si no aparece, se duplica el rango y se vuelve a cribar
        if let Some(casa) = regalos(limite, por_elfo, casas_por_elfo).iter().position(|&t| t >= objetivo) {
            return casa;
        }
        limite *= 2;
    }
}

pub fn part1(input: &str) -> Answer {
    Some(primera_casa(input.trim().parse().ok()?, 10, None).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(primera_casa(input.trim().parse().ok()?, 11, Some(50)).to_string()) // cada elfo reparte 11 veces su número y solo a 50 casas
}
