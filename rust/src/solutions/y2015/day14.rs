//! Advent of Code 2015 - Día 14
use crate::aoc::{ints, Answer};

const CARRERA: i64 = 2503; // segundos de la carrera
const CARRERA_EJEMPLO: i64 = 1000; // el ejemplo del enunciado (2 renos) dura 1000 s

/// (velocidad, segundos volando, segundos descansando) de cada reno.
fn leer(input: &str) -> Vec<(i64, i64, i64)> {
    input.lines().filter(|l| !l.trim().is_empty()).map(|l| {
        let n = ints(l);
        (n[0], n[1], n[2])
    }).collect()
}

fn distancia((velocidad, vuela, descansa): (i64, i64, i64), segundos: i64) -> i64 {
    let (ciclos, resto) = (segundos / (vuela + descansa), segundos % (vuela + descansa));
    velocidad * (ciclos * vuela + resto.min(vuela))
}

fn duracion(renos: &[(i64, i64, i64)]) -> i64 {
    if renos.len() <= 2 { CARRERA_EJEMPLO } else { CARRERA }
}

pub fn part1(input: &str) -> Answer {
    let renos = leer(input);
    Some(renos.iter().map(|&r| distancia(r, duracion(&renos))).max()?.to_string())
}

pub fn part2(input: &str) -> Answer {
    // cada segundo, el reno (o renos) que va en cabeza gana un punto
    let renos = leer(input);
    let mut puntos = vec![0; renos.len()];
    for segundo in 1..=duracion(&renos) {
        let distancias: Vec<i64> = renos.iter().map(|&r| distancia(r, segundo)).collect();
        let maxima = *distancias.iter().max()?;
        for (i, &d) in distancias.iter().enumerate() {
            puntos[i] += (d == maxima) as i64;
        }
    }
    Some(puntos.iter().max()?.to_string())
}
