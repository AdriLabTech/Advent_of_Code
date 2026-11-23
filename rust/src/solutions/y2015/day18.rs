//! Advent of Code 2015 - Día 18
use crate::aoc::Answer;

const PASOS: usize = 100;
const PASOS_EJEMPLO: (usize, usize) = (4, 5); // el ejemplo del enunciado (6x6) usa 4 pasos en la parte 1 y 5 en la parte 2

fn leer(input: &str) -> Vec<Vec<bool>> {
    input.lines().map(str::trim).filter(|l| !l.is_empty()).map(|l| l.chars().map(|c| c == '#').collect()).collect()
}

/// Una generación del juego de la vida (los vecinos fuera de la rejilla cuentan como apagados).
fn paso(luces: &[Vec<bool>]) -> Vec<Vec<bool>> {
    let lado = luces.len() as i32;
    (0..lado).map(|r| (0..lado).map(|c| {
        let vecinos = (-1..=1).flat_map(|dr| (-1..=1).map(move |dc| (dr, dc))).filter(|&(dr, dc)| (dr, dc) != (0, 0))
            .filter(|&(dr, dc)| (0..lado).contains(&(r + dr)) && (0..lado).contains(&(c + dc)) && luces[(r + dr) as usize][(c + dc) as usize]).count();
        vecinos == 3 || (vecinos == 2 && luces[r as usize][c as usize])
    }).collect()).collect()
}

fn animar(input: &str, esquinas_fijas: bool) -> usize {
    let mut luces = leer(input);
    let lado = luces.len();
    let pasos = if lado <= 6 { PASOS_EJEMPLO } else { (PASOS, PASOS) };
    let fijar = |l: &mut Vec<Vec<bool>>| {
        if esquinas_fijas {
            for (r, c) in [(0, 0), (0, lado - 1), (lado - 1, 0), (lado - 1, lado - 1)] {
                l[r][c] = true; // las cuatro esquinas están atascadas encendidas
            }
        }
    };
    fijar(&mut luces);
    for _ in 0..(if esquinas_fijas { pasos.1 } else { pasos.0 }) {
        luces = paso(&luces);
        fijar(&mut luces);
    }
    luces.iter().flatten().filter(|&&l| l).count()
}

pub fn part1(input: &str) -> Answer {
    Some(animar(input, false).to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(animar(input, true).to_string())
}
