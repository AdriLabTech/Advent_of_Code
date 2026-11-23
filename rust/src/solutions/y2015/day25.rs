//! Advent of Code 2015 - Día 25 (el input es 'Enter the code at row R, column C.')
use crate::aoc::{ints, Answer};

const PRIMER_CODIGO: u64 = 20151125;
const MULTIPLICADOR: u64 = 252533;
const MODULO: u64 = 33554393;

/// Código de la casilla (fila, columna): el papel se rellena por diagonales, así que primero se halla el
/// número de orden n de la casilla y luego se aplica n-1 veces el generador (con potencia modular, sin bucle).
fn codigo(fila: u64, columna: u64) -> u64 {
    let diagonal = fila + columna - 1; // las diagonales anteriores contienen 1 + 2 + ... + (diagonal-1) casillas
    let n = (diagonal - 1) * diagonal / 2 + columna;
    let (mut base, mut exponente, mut resultado) = (MULTIPLICADOR, n - 1, 1u64);
    while exponente > 0 {
        if exponente & 1 == 1 {
            resultado = resultado * base % MODULO;
        }
        base = base * base % MODULO;
        exponente >>= 1;
    }
    PRIMER_CODIGO * resultado % MODULO
}

pub fn part1(input: &str) -> Answer {
    let n = ints(input);
    Some(codigo(n[0] as u64, n[1] as u64).to_string())
}

pub fn part2(_input: &str) -> Answer {
    None // la parte 2 es la estrella final gratuita (no tiene puzzle)
}
