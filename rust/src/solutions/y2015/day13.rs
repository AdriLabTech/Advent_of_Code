//! Advent of Code 2015 - Día 13
use crate::aoc::Answer;
use std::collections::BTreeMap;

/// 'A would gain/lose N happiness units by sitting next to B.' -> felicidad[(A, B)] y lista de invitados.
fn leer(input: &str) -> (BTreeMap<(&str, &str), i32>, Vec<&str>) {
    let mut felicidad = BTreeMap::new();
    let mut invitados = Vec::new();
    for l in input.lines().filter(|l| !l.trim().is_empty()) {
        let p: Vec<&str> = l.trim_end_matches('.').split_whitespace().collect();
        let n: i32 = p[3].parse().unwrap();
        felicidad.insert((p[0], p[p.len() - 1]), if p[2] == "gain" { n } else { -n });
        if !invitados.contains(&p[0]) {
            invitados.push(p[0]);
        }
    }
    invitados.sort();
    (felicidad, invitados)
}

/// Mayor suma de felicidad en una mesa redonda (cada pareja de vecinos cuenta en los dos sentidos).
fn mejor_mesa(f: &BTreeMap<(&str, &str), i32>, invitados: &[&str]) -> i32 {
    fn permutar(mesa: &mut Vec<usize>, desde: usize, valor: &dyn Fn(usize, usize) -> i32, mejor: &mut i32) {
        if desde == mesa.len() {
            let n = mesa.len();
            let total: i32 = (0..n).map(|i| valor(mesa[i], mesa[(i + 1) % n])).sum();
            *mejor = (*mejor).max(total);
            return;
        }
        for i in desde..mesa.len() {
            mesa.swap(desde, i);
            permutar(mesa, desde + 1, valor, mejor);
            mesa.swap(desde, i);
        }
    }
    let valor = |a: usize, b: usize| f.get(&(invitados[a], invitados[b])).unwrap_or(&0) + f.get(&(invitados[b], invitados[a])).unwrap_or(&0);
    let mut mesa: Vec<usize> = (0..invitados.len()).collect();
    let mut mejor = i32::MIN;
    permutar(&mut mesa, 1, &valor, &mut mejor); // la mesa es circular: fijar el primero evita repetir giros
    mejor
}

pub fn part1(input: &str) -> Answer {
    let (f, invitados) = leer(input);
    Some(mejor_mesa(&f, &invitados).to_string())
}

pub fn part2(input: &str) -> Answer {
    let (f, mut invitados) = leer(input);
    invitados.push("Yo"); // yo me siento con felicidad 0 con todos
    invitados.sort();
    Some(mejor_mesa(&f, &invitados).to_string())
}
