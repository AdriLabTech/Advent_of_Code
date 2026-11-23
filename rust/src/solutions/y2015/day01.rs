//! Advent of Code 2015 - Día 1
use crate::aoc::Answer;

fn paso(piso: i64, c: char) -> i64 {
    match c {
        '(' => piso + 1,
        ')' => piso - 1,
        _ => piso,
    }
}

pub fn part1(input: &str) -> Answer {
    let piso = input.lines().next()?.chars().fold(0, paso);
    Some(piso.to_string())
}

/// Posición (empezando en 1) del primer carácter que lleva al piso -1.
pub fn part2(input: &str) -> Answer {
    let mut piso = 0;
    for (i, c) in input.lines().next()?.chars().enumerate() {
        piso = paso(piso, c);
        if piso == -1 {
            return Some((i + 1).to_string());
        }
    }
    None // nunca entra en el sótano
}
