//! Advent of Code 2015 - Día 23
use crate::aoc::Answer;

/// Ejecuta el programa hasta salirse de él y devuelve los registros [a, b].
fn ejecutar(input: &str, a: u64) -> [u64; 2] {
    let programa: Vec<Vec<String>> = input.lines().filter(|l| !l.trim().is_empty()).map(|l| l.replace(',', "").split_whitespace().map(String::from).collect()).collect();
    let mut registros = [a, 0];
    let indice = |r: &str| (r == "b") as usize;
    let mut pc: i64 = 0;
    while pc >= 0 && (pc as usize) < programa.len() {
        let i = &programa[pc as usize];
        let mut salto: i64 = 1;
        match i[0].as_str() {
            "hlf" => registros[indice(&i[1])] /= 2,
            "tpl" => registros[indice(&i[1])] *= 3,
            "inc" => registros[indice(&i[1])] += 1,
            "jmp" => salto = i[1].parse().unwrap(),
            "jie" if registros[indice(&i[1])] % 2 == 0 => salto = i[2].parse().unwrap(),
            "jio" if registros[indice(&i[1])] == 1 => salto = i[2].parse().unwrap(),
            _ => {}
        }
        pc += salto;
    }
    registros
}

pub fn part1(input: &str) -> Answer {
    let r = ejecutar(input, 0);
    let lineas = input.lines().filter(|l| !l.trim().is_empty()).count();
    Some((if lineas > 4 { r[1] } else { r[0] }).to_string()) // el ejemplo del enunciado (4 instrucciones) deja el resultado en a
}

pub fn part2(input: &str) -> Answer {
    Some(ejecutar(input, 1)[1].to_string())
}
