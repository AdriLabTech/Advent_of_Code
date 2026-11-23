//! Advent of Code 2015 - Día 11
use crate::aoc::Answer;

/// Suma uno como si fuera un número en base 26 (z pasa a a y acarrea). Salta de golpe las que tienen i, o o l.
fn incrementar(clave: &mut [u8]) {
    if let Some(i) = clave.iter().position(|c| b"iol".contains(c)) {
        clave[i] += 1; // si ya hay una letra prohibida, todo lo que va detrás se pone a 'a'
        clave[i + 1..].fill(b'a');
        return;
    }
    for c in clave.iter_mut().rev() {
        if *c == b'z' {
            *c = b'a';
        } else {
            *c += 1;
            break;
        }
    }
}

fn es_valida(clave: &[u8]) -> bool {
    let escalera = clave.windows(3).any(|t| t[0] + 1 == t[1] && t[1] + 1 == t[2]);
    let sin_prohibidas = !clave.iter().any(|c| b"iol".contains(c));
    let mut letras_dobles: Vec<u8> = clave.windows(2).filter(|p| p[0] == p[1]).map(|p| p[0]).collect();
    letras_dobles.sort();
    letras_dobles.dedup(); // dos letras distintas dobles
    escalera && sin_prohibidas && letras_dobles.len() >= 2
}

fn siguiente_clave(clave: &str) -> String {
    let mut c = clave.as_bytes().to_vec();
    incrementar(&mut c);
    while !es_valida(&c) {
        incrementar(&mut c);
    }
    String::from_utf8(c).unwrap()
}

pub fn part1(input: &str) -> Answer {
    Some(siguiente_clave(input.lines().next()?.trim()))
}

pub fn part2(input: &str) -> Answer {
    Some(siguiente_clave(&siguiente_clave(input.lines().next()?.trim())))
}
