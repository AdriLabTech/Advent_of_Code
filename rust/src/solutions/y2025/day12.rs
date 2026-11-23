//! Advent of Code 2025 - Día 12
use crate::aoc::{paragraphs, Answer};
use std::collections::{BTreeSet, HashMap};

type Celda = (i32, i32);

/// Formas ('0:' + filas) y regiones ('AxB: q0 q1 ...').
fn leer(input: &str) -> (HashMap<usize, Vec<Celda>>, Vec<(usize, usize, Vec<usize>)>) {
    let (mut formas, mut regiones) = (HashMap::new(), Vec::new());
    for bloque in paragraphs(input) {
        if let Some(indice) = bloque[0].strip_suffix(':') {
            let celdas = bloque[1..]
                .iter()
                .enumerate()
                .flat_map(|(r, fila)| fila.chars().enumerate().filter(|&(_, ch)| ch == '#').map(move |(c, _)| (r as i32, c as i32)))
                .collect();
            formas.insert(indice.parse().unwrap(), celdas);
        } else {
            for linea in bloque {
                let (tam, cantidades) = linea.split_once(':').unwrap();
                let (ancho, alto) = tam.split_once('x').unwrap();
                regiones.push((ancho.parse().unwrap(), alto.parse().unwrap(), cantidades.split_whitespace().map(|q| q.parse().unwrap()).collect()));
            }
        }
    }
    (formas, regiones)
}

/// Las rotaciones y reflejos distintos de una forma, normalizados a la esquina superior izquierda.
fn orientaciones(forma: &[Celda]) -> Vec<Vec<Celda>> {
    let mut resultado = BTreeSet::new();
    let mut celdas = forma.to_vec();
    for _ in 0..4 {
        celdas = celdas.iter().map(|&(r, c)| (c, -r)).collect(); // rotar 90°
        for espejo in [celdas.clone(), celdas.iter().map(|&(r, c)| (r, -c)).collect::<Vec<_>>()] {
            let (menor_r, menor_c) = (espejo.iter().map(|p| p.0).min().unwrap(), espejo.iter().map(|p| p.1).min().unwrap());
            let mut normal: Vec<Celda> = espejo.iter().map(|&(r, c)| (r - menor_r, c - menor_c)).collect();
            normal.sort();
            resultado.insert(normal);
        }
    }
    resultado.into_iter().collect()
}

struct Tablero<'a> {
    ancho: usize,
    alto: usize,
    libres: Vec<bool>,
    restantes: Vec<usize>,
    orient: &'a HashMap<usize, Vec<Vec<Celda>>>,
}

impl Tablero<'_> {
    /// Rellena la primera celda libre (por filas) con una pieza o la deja vacía (si queda holgura).
    fn resolver(&mut self, mut pos: usize, hueco: usize) -> bool {
        while pos < self.ancho * self.alto && !self.libres[pos] {
            pos += 1;
        }
        if pos == self.ancho * self.alto {
            return self.restantes.iter().all(|&q| q == 0);
        }
        let (r0, c0) = ((pos / self.ancho) as i32, (pos % self.ancho) as i32);
        for i in 0..self.restantes.len() {
            if self.restantes[i] == 0 {
                continue;
            }
            for orient in &self.orient[&i] {
                // la primera celda de la forma (por filas) es la que se apoya en la celda libre
                let (dr, dc) = orient[0];
                let destino: Vec<Celda> = orient.iter().map(|&(r, c)| (r0 + r - dr, c0 + c - dc)).collect();
                let cabe = destino.iter().all(|&(r, c)| r >= 0 && c >= 0 && (r as usize) < self.alto && (c as usize) < self.ancho && self.libres[r as usize * self.ancho + c as usize]);
                if !cabe {
                    continue;
                }
                for &(r, c) in &destino {
                    self.libres[r as usize * self.ancho + c as usize] = false;
                }
                self.restantes[i] -= 1;
                if self.resolver(pos + 1, hueco) {
                    return true;
                }
                self.restantes[i] += 1;
                for &(r, c) in &destino {
                    self.libres[r as usize * self.ancho + c as usize] = true;
                }
            }
        }
        if hueco > 0 {
            self.libres[pos] = false; // dejar esta celda vacía
            if self.resolver(pos + 1, hueco - 1) {
                return true;
            }
            self.libres[pos] = true;
        }
        false
    }
}

fn cabe(ancho: usize, alto: usize, cantidades: &[usize], orient: &HashMap<usize, Vec<Vec<Celda>>>, tamanos: &HashMap<usize, usize>) -> bool {
    let piezas: usize = cantidades.iter().sum();
    let celdas: usize = cantidades.iter().enumerate().map(|(i, q)| q * tamanos[&i]).sum();
    if celdas > ancho * alto {
        return false; // no caben ni sin huecos
    }
    if piezas <= (ancho / 3) * (alto / 3) {
        return true; // cada pieza cabe en un cuadrado de 3x3 y hay sitio para todos esos cuadrados
    }
    // búsqueda exacta
    let mut t = Tablero { ancho, alto, libres: vec![true; ancho * alto], restantes: cantidades.to_vec(), orient };
    t.resolver(0, ancho * alto - celdas)
}

pub fn part1(input: &str) -> Answer {
    let (formas, regiones) = leer(input);
    let orient: HashMap<usize, Vec<Vec<Celda>>> = formas.iter().map(|(&i, f)| (i, orientaciones(f))).collect();
    let tamanos: HashMap<usize, usize> = formas.iter().map(|(&i, f)| (i, f.len())).collect();
    let total = regiones.iter().filter(|(ancho, alto, q)| cabe(*ancho, *alto, q, &orient, &tamanos)).count();
    Some(total.to_string())
}

pub fn part2(_input: &str) -> Answer {
    None // pendiente: la parte 2 se desbloquea al completar el resto de días
}
