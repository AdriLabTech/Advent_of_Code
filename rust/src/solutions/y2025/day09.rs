//! Advent of Code 2025 - Día 9
use crate::aoc::Answer;
use std::collections::{BTreeSet, HashMap, HashSet, VecDeque};

type Punto = (i64, i64);

fn leer(input: &str) -> Vec<Punto> {
    input
        .lines()
        .filter(|l| !l.trim().is_empty())
        .map(|l| {
            let (x, y) = l.split_once(',').expect("línea sin coma");
            (x.trim().parse().unwrap(), y.trim().parse().unwrap())
        })
        .collect()
}

fn area(a: Punto, b: Punto) -> i64 {
    ((a.0 - b.0).abs() + 1) * ((a.1 - b.1).abs() + 1)
}

pub fn part1(input: &str) -> Answer {
    let puntos: Vec<Punto> = leer(input).into_iter().collect::<HashSet<_>>().into_iter().collect();
    let mejor = (0..puntos.len()).flat_map(|i| (i + 1..puntos.len()).map(move |j| (i, j))).map(|(i, j)| area(puntos[i], puntos[j])).max()?;
    Some(mejor.to_string())
}

pub fn part2(input: &str) -> Answer {
    let rojas = leer(input);

    // 1) Compresión de coordenadas: solo importan los valores usados (y sus vecinos, para tener borde exterior)
    let xs: Vec<i64> = rojas.iter().flat_map(|p| [p.0 - 1, p.0, p.0 + 1]).collect::<BTreeSet<_>>().into_iter().collect();
    let ys: Vec<i64> = rojas.iter().flat_map(|p| [p.1 - 1, p.1, p.1 + 1]).collect::<BTreeSet<_>>().into_iter().collect();
    let ix: HashMap<i64, usize> = xs.iter().enumerate().map(|(i, &x)| (x, i)).collect();
    let iy: HashMap<i64, usize> = ys.iter().enumerate().map(|(i, &y)| (y, i)).collect();
    let (alto, ancho) = (ys.len(), xs.len());

    // 2) Borde del polígono (los lados unen cada punto con el siguiente)
    let mut borde = vec![vec![false; ancho]; alto];
    for k in 0..rojas.len() {
        let (a, b) = (rojas[k], rojas[(k + 1) % rojas.len()]);
        for y in iy[&a.1].min(iy[&b.1])..=iy[&a.1].max(iy[&b.1]) {
            for x in ix[&a.0].min(ix[&b.0])..=ix[&a.0].max(ix[&b.0]) {
                borde[y][x] = true;
            }
        }
    }

    // 3) Relleno desde fuera: lo que no se alcanza está dentro del polígono
    let mut exterior = vec![vec![false; ancho]; alto];
    let mut cola = VecDeque::new();
    for y in 0..alto {
        for x in 0..ancho {
            if (y == 0 || y == alto - 1 || x == 0 || x == ancho - 1) && !borde[y][x] {
                exterior[y][x] = true;
                cola.push_back((y, x));
            }
        }
    }
    while let Some((y, x)) = cola.pop_front() {
        for (dy, dx) in [(-1i64, 0i64), (1, 0), (0, -1), (0, 1)] {
            let (ny, nx) = (y as i64 + dy, x as i64 + dx);
            if ny < 0 || nx < 0 || ny >= alto as i64 || nx >= ancho as i64 {
                continue;
            }
            let (ny, nx) = (ny as usize, nx as usize);
            if !borde[ny][nx] && !exterior[ny][nx] {
                exterior[ny][nx] = true;
                cola.push_back((ny, nx));
            }
        }
    }

    // 4) Sumas acumuladas 2D de las celdas permitidas (borde o interior)
    let mut suma = vec![vec![0i64; ancho + 1]; alto + 1];
    for y in 0..alto {
        for x in 0..ancho {
            let permitida = (borde[y][x] || !exterior[y][x]) as i64;
            suma[y + 1][x + 1] = suma[y][x + 1] + suma[y + 1][x] - suma[y][x] + permitida;
        }
    }

    // 5) Mayor rectángulo cuyas celdas están todas permitidas
    let mut mejor = 0;
    for i in 0..rojas.len() {
        for j in i + 1..rojas.len() {
            let (p1, p2) = (rojas[i], rojas[j]);
            let a = area(p1, p2);
            if a <= mejor {
                continue;
            }
            let (x1, x2) = (ix[&p1.0].min(ix[&p2.0]), ix[&p1.0].max(ix[&p2.0]));
            let (y1, y2) = (iy[&p1.1].min(iy[&p2.1]), iy[&p1.1].max(iy[&p2.1]));
            let dentro = suma[y2 + 1][x2 + 1] - suma[y1][x2 + 1] - suma[y2 + 1][x1] + suma[y1][x1];
            if dentro == ((x2 - x1 + 1) * (y2 - y1 + 1)) as i64 {
                mejor = a;
            }
        }
    }
    Some(mejor.to_string())
}
