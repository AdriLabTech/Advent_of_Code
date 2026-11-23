//! Advent of Code 2015 - Día 7
use crate::aoc::Answer;
use std::collections::HashMap;

type Gates<'a> = HashMap<&'a str, Vec<&'a str>>;

fn leer(input: &str) -> Gates<'_> {
    input
        .lines()
        .filter(|l| !l.trim().is_empty())
        .map(|l| {
            let (origen, destino) = l.split_once(" -> ").expect("línea sin ->");
            (destino.trim(), origen.split_whitespace().collect())
        })
        .collect()
}

/// Señal de un cable (o número). `forzado` sustituye la señal de un cable.
fn valor<'a>(token: &'a str, gates: &Gates<'a>, memo: &mut HashMap<&'a str, u16>, forzado: Option<(&str, u16)>) -> u16 {
    if let Ok(n) = token.parse::<u16>() {
        return n;
    }
    if let Some((cable, v)) = forzado {
        if cable == token {
            return v;
        }
    }
    if let Some(&m) = memo.get(token) {
        return m;
    }
    let g = &gates[token];
    let resultado = match g.len() {
        1 => valor(g[0], gates, memo, forzado), // 123 -> x  /  a -> b
        2 => !valor(g[1], gates, memo, forzado), // NOT x
        _ => {
            let (a, b) = (valor(g[0], gates, memo, forzado), valor(g[2], gates, memo, forzado));
            match g[1] {
                "AND" => a & b,
                "OR" => a | b,
                "LSHIFT" => a << b,
                _ => a >> b, // RSHIFT
            }
        }
    };
    memo.insert(token, resultado);
    resultado
}

pub fn part1(input: &str) -> Answer {
    let gates = leer(input);
    gates.contains_key("a").then(|| valor("a", &gates, &mut HashMap::new(), None).to_string()) // el ejemplo no tiene cable a
}

pub fn part2(input: &str) -> Answer {
    // la señal de a (parte 1) se pasa al cable b y se recalcula todo
    let gates = leer(input);
    if !gates.contains_key("a") {
        return None;
    }
    let a = valor("a", &gates, &mut HashMap::new(), None);
    Some(valor("a", &gates, &mut HashMap::new(), Some(("b", a))).to_string())
}
