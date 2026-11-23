//! Advent of Code 2025 - Día 8
use crate::aoc::Answer;

const CONEXIONES: usize = 1000; // pares más cercanos que se conectan en la parte 1
const CONEXIONES_EJEMPLO: usize = 10; // el ejemplo del enunciado (20 cajas) conecta solo 10

struct Circuitos {
    padre: Vec<usize>,
    tamano: Vec<usize>,
}

impl Circuitos {
    fn raiz(&mut self, mut i: usize) -> usize {
        while self.padre[i] != i {
            self.padre[i] = self.padre[self.padre[i]];
            i = self.padre[i];
        }
        i
    }

    /// Une los circuitos de i y j. Devuelve false si ya estaban unidos.
    fn unir(&mut self, i: usize, j: usize) -> bool {
        let (mut ri, mut rj) = (self.raiz(i), self.raiz(j));
        if ri == rj {
            return false;
        }
        if self.tamano[ri] < self.tamano[rj] {
            std::mem::swap(&mut ri, &mut rj);
        }
        self.padre[rj] = ri;
        self.tamano[ri] += self.tamano[rj];
        true
    }
}

fn leer(input: &str) -> Vec<[i64; 3]> {
    input
        .lines()
        .filter(|l| !l.trim().is_empty())
        .map(|l| {
            let v: Vec<i64> = l.split(',').map(|n| n.trim().parse().unwrap()).collect();
            [v[0], v[1], v[2]]
        })
        .collect()
}

/// Recorre los pares por distancia creciente (Kruskal) y une los circuitos de cada par.
/// Se detiene tras `limite_pares` pares (cuenten o no como unión) o al quedar un solo circuito.
/// Devuelve (tamaños de los circuitos, último par que unió dos circuitos distintos).
fn conectar(cajas: &[[i64; 3]], limite_pares: Option<usize>) -> (Vec<usize>, Option<(usize, usize)>) {
    let n = cajas.len();
    let mut pares: Vec<(i64, usize, usize)> = (0..n)
        .flat_map(|i| ((i + 1)..n).map(move |j| (i, j)))
        .map(|(i, j)| ((0..3).map(|k| (cajas[i][k] - cajas[j][k]).pow(2)).sum(), i, j))
        .collect();
    pares.sort();

    let mut c = Circuitos { padre: (0..n).collect(), tamano: vec![1; n] };
    let (mut circuitos, mut ultimo) = (n, None);
    for (visitados, &(_, i, j)) in pares.iter().enumerate() {
        if Some(visitados) == limite_pares || circuitos == 1 {
            break;
        }
        if c.unir(i, j) {
            // si ya estaban en el mismo circuito no pasa nada
            circuitos -= 1;
            ultimo = Some((i, j));
        }
    }
    ((0..n).filter(|&i| c.padre[i] == i).map(|i| c.tamano[i]).collect(), ultimo)
}

pub fn part1(input: &str) -> Answer {
    let cajas = leer(input);
    let (mut tamanos, _) = conectar(&cajas, Some(if cajas.len() <= 20 { CONEXIONES_EJEMPLO } else { CONEXIONES }));
    tamanos.sort_by(|a, b| b.cmp(a));
    Some(tamanos.iter().take(3).product::<usize>().to_string())
}

pub fn part2(input: &str) -> Answer {
    let cajas = leer(input);
    let (_, ultimo) = conectar(&cajas, None); // la última unión es la que deja un solo circuito
    let (i, j) = ultimo?;
    Some((cajas[i][0] * cajas[j][0]).to_string())
}
