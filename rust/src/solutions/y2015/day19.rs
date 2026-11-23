//! Advent of Code 2015 - Día 19
use crate::aoc::Answer;
use std::collections::HashSet;

/// Reemplazos 'X => Y', una línea en blanco y la molécula.
fn leer(input: &str) -> (Vec<(&str, &str)>, &str) {
    let reemplazos = input.lines().filter_map(|l| l.split_once(" => ")).collect();
    let molecula = input.lines().map(str::trim).rfind(|l| !l.is_empty() && !l.contains(" => ")).unwrap();
    (reemplazos, molecula)
}

pub fn part1(input: &str) -> Answer {
    let (reemplazos, molecula) = leer(input);
    let mut resultados = HashSet::new();
    for (origen, destino) in reemplazos {
        for (i, _) in molecula.match_indices(origen) {
            // cada aparición del origen es un reemplazo posible
            resultados.insert(format!("{}{}{}", &molecula[..i], destino, &molecula[i + origen.len()..]));
        }
    }
    Some(resultados.len().to_string())
}

/// Pasos mínimos de 'e' a la molécula: búsqueda en anchura hacia atrás (de la molécula a 'e'). Solo sirve para moléculas cortas.
fn pasos_busqueda(reemplazos: &[(&str, &str)], molecula: &str) -> usize {
    let mut actual: HashSet<String> = HashSet::from([molecula.to_string()]);
    let mut pasos = 0;
    while !actual.contains("e") {
        pasos += 1;
        let mut siguiente = HashSet::new();
        for m in &actual {
            for &(origen, destino) in reemplazos {
                for (i, _) in m.match_indices(destino) {
                    let nueva = format!("{}{}{}", &m[..i], origen, &m[i + destino.len()..]);
                    if origen != "e" || nueva == "e" {
                        siguiente.insert(nueva); // 'e' solo vale como paso final
                    }
                }
            }
        }
        actual = siguiente;
    }
    pasos
}

pub fn part2(input: &str) -> Answer {
    let (reemplazos, molecula) = leer(input);
    if !molecula.contains("Rn") {
        return Some(pasos_busqueda(&reemplazos, molecula).to_string());
    }
    // Molécula real: cada reemplazo suma un elemento, salvo los de la forma X => X Rn ... Ar (que añaden Rn y Ar)
    // y los que llevan Y (cada Y añade además una coma y otro elemento). Por eso los pasos son:
    // elementos - (Rn + Ar) - 2 * Y - 1
    let elementos = molecula.chars().filter(|c| c.is_ascii_uppercase()).count();
    let (rn, ar, y) = (molecula.matches("Rn").count(), molecula.matches("Ar").count(), molecula.matches('Y').count());
    Some((elementos - rn - ar - 2 * y - 1).to_string())
}
