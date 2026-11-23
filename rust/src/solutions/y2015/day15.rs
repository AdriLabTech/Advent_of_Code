//! Advent of Code 2015 - Día 15
use crate::aoc::{ints, Answer};

const CUCHARADAS: i64 = 100;

/// Prueba todos los repartos de las cucharadas entre los ingredientes y devuelve la mejor puntuación.
fn mejor_galleta(input: &str, calorias: Option<i64>) -> i64 {
    // capacidad, durabilidad, sabor, textura, calorías
    let ingredientes: Vec<Vec<i64>> = input.lines().filter(|l| !l.trim().is_empty()).map(|l| ints(l.split(':').nth(1).unwrap())).collect();

    fn repartir(i: usize, restantes: i64, propiedades: [i64; 5], ing: &[Vec<i64>], calorias: Option<i64>, mejor: &mut i64) {
        if i == ing.len() - 1 {
            // el último ingrediente se lleva lo que queda
            let p: Vec<i64> = (0..5).map(|k| propiedades[k] + restantes * ing[i][k]).collect();
            if calorias.is_none_or(|c| c == p[4]) {
                *mejor = (*mejor).max(p[..4].iter().map(|&v| v.max(0)).product()); // un total negativo cuenta como 0
            }
            return;
        }
        for cantidad in 0..=restantes {
            let mut nuevas = propiedades;
            for k in 0..5 {
                nuevas[k] += cantidad * ing[i][k];
            }
            repartir(i + 1, restantes - cantidad, nuevas, ing, calorias, mejor);
        }
    }
    let mut mejor = 0;
    repartir(0, CUCHARADAS, [0; 5], &ingredientes, calorias, &mut mejor);
    mejor
}

pub fn part1(input: &str) -> Answer {
    Some(mejor_galleta(input, None).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(mejor_galleta(input, Some(500)).to_string())
}
