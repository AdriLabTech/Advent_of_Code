//! Advent of Code 2015 - Día 8
use crate::aoc::Answer;

/// Caracteres del valor de un literal: cada escape (\\, \", \xNN) cuenta como uno; las comillas exteriores no cuentan.
fn en_memoria(literal: &str) -> usize {
    let c: Vec<char> = literal[1..literal.len() - 1].chars().collect();
    let (mut i, mut n) = (0, 0);
    while i < c.len() {
        i += if c[i] == '\\' { if c[i + 1] == 'x' { 4 } else { 2 } } else { 1 };
        n += 1;
    }
    n
}

/// Caracteres de la cadena codificada de nuevo: comillas exteriores y \ y " escapadas.
fn codificado(literal: &str) -> usize {
    literal.len() + 2 + literal.matches(['\\', '"']).count()
}

fn literales(input: &str) -> impl Iterator<Item = &str> {
    input.lines().map(str::trim).filter(|l| !l.is_empty())
}

pub fn part1(input: &str) -> Answer {
    Some(literales(input).map(|l| l.len() - en_memoria(l)).sum::<usize>().to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(literales(input).map(|l| codificado(l) - l.len()).sum::<usize>().to_string())
}
