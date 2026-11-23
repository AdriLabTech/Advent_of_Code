//! Advent of Code 2025 - Día 2
use crate::aoc::Answer;

/// Líneas 'a-b,c-d,...' como lista de (a, b).
fn rangos(input: &str) -> Vec<(u128, u128)> {
    input
        .split([',', '\n'])
        .map(str::trim)
        .filter(|r| !r.is_empty())
        .map(|r| {
            let (a, b) = r.split_once('-').expect("rango sin guion");
            (a.parse().unwrap(), b.parse().unwrap())
        })
        .collect()
}

/// Suma de los números de `largo` dígitos en [a, b] formados repitiendo un bloque de `periodo` dígitos.
fn suma_con_periodo(a: u128, b: u128, largo: u32, periodo: u32) -> u128 {
    let (a, b) = (a.max(10u128.pow(largo - 1)), b.min(10u128.pow(largo) - 1));
    let m = (10u128.pow(largo) - 1) / (10u128.pow(periodo) - 1); // n = x * m con x de `periodo` dígitos
    let menor = 10u128.pow(periodo - 1).max(a.div_ceil(m));
    let mayor = (10u128.pow(periodo) - 1).min(b / m);
    if menor <= mayor { m * (menor + mayor) * (mayor - menor + 1) / 2 } else { 0 }
}

pub fn part1(input: &str) -> Answer {
    // ID inválido = un bloque repetido exactamente dos veces: periodo = mitad de los dígitos
    let total: u128 = rangos(input)
        .iter()
        .flat_map(|&(a, b)| (2..=b.to_string().len() as u32).step_by(2).map(move |largo| suma_con_periodo(a, b, largo, largo / 2)))
        .sum();
    Some(total.to_string())
}

pub fn part2(input: &str) -> Answer {
    // ahora vale cualquier número de repeticiones (>= 2): un periodo p < largo que divida al largo.
    // Un mismo número puede tener varios periodos (111111 -> 1, 2 y 3), así que se suma por periodo
    // mínimo exacto: g[p] = (números con periodo p) - (los que ya tienen un periodo menor que divide a p)
    let mut total: i128 = 0;
    for (a, b) in rangos(input) {
        for largo in 2..=b.to_string().len() as u32 {
            let mut g: Vec<(u32, i128)> = Vec::new();
            for p in (1..largo).filter(|p| largo % p == 0) {
                let ya_contados: i128 = g.iter().filter(|(d, _)| p % d == 0).map(|(_, v)| v).sum();
                g.push((p, suma_con_periodo(a, b, largo, p) as i128 - ya_contados));
            }
            total += g.iter().map(|(_, v)| v).sum::<i128>();
        }
    }
    Some(total.to_string())
}
