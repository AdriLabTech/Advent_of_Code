//! Advent of Code 2015 - Día 24
use crate::aoc::Answer;

/// ¿Se pueden repartir los paquetes en `grupos` grupos de `peso` cada uno?
fn se_puede_repartir(paquetes: &[u64], grupos: u32, peso: u64) -> bool {
    if grupos == 1 {
        return paquetes.iter().sum::<u64>() == peso;
    }
    let mut hallado = false;
    combinaciones(paquetes, peso, &mut |grupo| {
        let resto: Vec<u64> = paquetes.iter().copied().filter(|p| !grupo.contains(p)).collect();
        hallado = se_puede_repartir(&resto, grupos - 1, peso);
        !hallado // seguir buscando mientras no se haya hallado
    });
    hallado
}

/// Recorre los subconjuntos de `paquetes` que suman `peso`; se detiene cuando `f` devuelve false.
fn combinaciones(paquetes: &[u64], peso: u64, f: &mut dyn FnMut(&[u64]) -> bool) {
    fn rec(paquetes: &[u64], desde: usize, resta: u64, actual: &mut Vec<u64>, f: &mut dyn FnMut(&[u64]) -> bool) -> bool {
        if resta == 0 {
            return f(actual);
        }
        for i in desde..paquetes.len() {
            if paquetes[i] <= resta {
                actual.push(paquetes[i]);
                let seguir = rec(paquetes, i + 1, resta - paquetes[i], actual, f);
                actual.pop();
                if !seguir {
                    return false;
                }
            }
        }
        true
    }
    rec(paquetes, 0, peso, &mut Vec::new(), f);
}

fn mejor_entrelazamiento(input: &str, grupos: u32) -> Option<u64> {
    let paquetes: Vec<u64> = input.lines().filter(|l| !l.trim().is_empty()).map(|l| l.trim().parse().unwrap()).collect();
    let peso = paquetes.iter().sum::<u64>() / grupos as u64;
    // se buscan todos los primeros grupos que suman el peso; interesa el de menos paquetes y, a igualdad, el de menor producto
    let mut mejor: Option<(usize, u64)> = None;
    combinaciones(&paquetes, peso, &mut |grupo| {
        let clave = (grupo.len(), grupo.iter().product::<u64>());
        if mejor.is_none_or(|m| clave < m) {
            let resto: Vec<u64> = paquetes.iter().copied().filter(|p| !grupo.contains(p)).collect();
            if se_puede_repartir(&resto, grupos - 1, peso) {
                mejor = Some(clave);
            }
        }
        true
    });
    mejor.map(|m| m.1)
}

pub fn part1(input: &str) -> Answer {
    Some(mejor_entrelazamiento(input, 3)?.to_string())
}

pub fn part2(input: &str) -> Answer {
    Some(mejor_entrelazamiento(input, 4)?.to_string())
}
