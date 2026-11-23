//! Advent of Code 2025 - Día 6
use crate::aoc::Answer;
use std::collections::BTreeMap;

pub fn part1(input: &str) -> Answer {
    // cada columna de la hoja: varios números y, al final, el operador
    let mut columnas: BTreeMap<usize, Vec<&str>> = BTreeMap::new();
    for line in input.lines().filter(|l| !l.trim().is_empty()) {
        let tokens: Vec<&str> = if line.contains('*') {
            line.matches(['*', '+']).collect()
        } else {
            line.split(|c: char| !c.is_ascii_digit()).filter(|t| !t.is_empty()).collect()
        };
        for (i, t) in tokens.into_iter().enumerate() {
            columnas.entry(i).or_default().push(t);
        }
    }

    let mut total: u128 = 0;
    for col in columnas.values() {
        let (operador, numeros) = col.split_last().unwrap();
        let mut valores = numeros.iter().map(|n| n.parse::<u128>().unwrap());
        let primero = valores.next().unwrap();
        total += match *operador {
            "+" => valores.fold(primero, |a, b| a + b),
            "*" => valores.fold(primero, |a, b| a * b),
            _ => primero,
        };
    }
    Some(total.to_string())
}

pub fn part2(input: &str) -> Answer {
    // se lee carácter a carácter: cada columna de la hoja es un número y el operador marca el grupo
    let filas: Vec<&[u8]> = input.lines().filter(|l| !l.trim().is_empty()).map(str::as_bytes).collect();
    let ancho = filas.iter().map(|f| f.len()).max()?;
    let (mut total, mut acumulado): (u128, Option<u128>) = (0, None);
    let (mut en_grupo, mut multiplica) = (false, false);
    for i in 0..ancho {
        let columna: Vec<u8> = filas.iter().filter(|f| i < f.len()).map(|f| f[i]).collect();
        let (operador, digitos) = columna.split_last().unwrap();
        if *operador == b'+' || *operador == b'*' {
            // empieza un grupo nuevo
            (multiplica, en_grupo, acumulado) = (*operador == b'*', true, None);
        }
        let texto = String::from_utf8_lossy(digitos);
        let texto = texto.trim();
        if texto.is_empty() {
            // columna vacía = fin del grupo
            if en_grupo {
                total += acumulado.unwrap_or(0);
            }
            en_grupo = false;
            continue;
        }
        let valor: u128 = texto.parse().expect("columna no numérica");
        acumulado = Some(match acumulado {
            None => valor,
            Some(a) if multiplica => a * valor,
            Some(a) => a + valor,
        });
    }
    if en_grupo {
        total += acumulado.unwrap_or(0); // el último grupo no tiene columna vacía detrás
    }
    Some(total.to_string())
}
