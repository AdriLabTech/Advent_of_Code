//! Advent of Code 2015 - Día 12
use crate::aoc::{ints, Answer};

/// Suma de todos los números ignorando los objetos {...} que tengan algún valor "red" (los arrays no cuentan como objeto).
/// Se recorre el texto con una pila: cada { o [ abre un nivel con su suma; al cerrarlo se suma al nivel de fuera
/// (salvo un objeto con "red", que aporta 0).
fn suma_sin_rojos(texto: &str) -> i64 {
    struct Nivel {
        suma: i64,
        es_objeto: bool,
        tiene_rojo: bool,
    }
    let c = texto.as_bytes();
    let mut pila = vec![Nivel { suma: 0, es_objeto: false, tiene_rojo: false }];
    let mut i = 0;
    while i < c.len() {
        match c[i] {
            b'{' | b'[' => pila.push(Nivel { suma: 0, es_objeto: c[i] == b'{', tiene_rojo: false }),
            b'}' | b']' => {
                let n = pila.pop().unwrap();
                pila.last_mut().unwrap().suma += if n.tiene_rojo { 0 } else { n.suma };
            }
            b'"' => {
                let fin = i + 1 + c[i + 1..].iter().position(|&x| x == b'"').unwrap();
                let es_clave = c.get(fin + 1) == Some(&b':'); // un ':' detrás significa que era una clave, no un valor
                let nivel = pila.last_mut().unwrap();
                if &c[i + 1..fin] == b"red" && nivel.es_objeto && !es_clave {
                    nivel.tiene_rojo = true;
                }
                i = fin;
            }
            b'-' | b'0'..=b'9' => {
                let mut fin = i + 1;
                while fin < c.len() && c[fin].is_ascii_digit() {
                    fin += 1;
                }
                pila.last_mut().unwrap().suma += texto[i..fin].parse::<i64>().unwrap();
                i = fin - 1;
            }
            _ => {}
        }
        i += 1;
    }
    pila[0].suma
}

pub fn part1(input: &str) -> Answer {
    Some(ints(input.lines().next()?).iter().sum::<i64>().to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(suma_sin_rojos(input.lines().next()?).to_string())
}
