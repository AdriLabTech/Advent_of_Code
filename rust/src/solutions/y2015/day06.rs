//! Advent of Code 2015 - Día 6
use crate::aoc::{ints, Answer};

const LADO: usize = 1000;

#[derive(Clone, Copy, PartialEq)]
enum Accion {
    On,
    Off,
    Toggle,
}

/// Devuelve (accion, x1, y1, x2, y2) con x1<=x2 e y1<=y2.
fn instrucciones(input: &str) -> Vec<(Accion, usize, usize, usize, usize)> {
    input
        .lines()
        .filter(|l| !l.trim().is_empty())
        .map(|l| {
            let accion = if l.starts_with("turn on") {
                Accion::On
            } else if l.starts_with("turn off") {
                Accion::Off
            } else {
                Accion::Toggle
            };
            let n = ints(l);
            let (x1, y1, x2, y2) = (n[0] as usize, n[1] as usize, n[2] as usize, n[3] as usize);
            (accion, x1.min(x2), y1.min(y2), x1.max(x2), y1.max(y2))
        })
        .collect()
}

pub fn part1(input: &str) -> Answer {
    let mut luces = vec![false; LADO * LADO];
    for (accion, x1, y1, x2, y2) in instrucciones(input) {
        for y in y1..=y2 {
            for luz in &mut luces[y * LADO + x1..=y * LADO + x2] {
                *luz = match accion {
                    Accion::On => true,
                    Accion::Off => false,
                    Accion::Toggle => !*luz,
                };
            }
        }
    }
    Some(luces.iter().filter(|&&l| l).count().to_string())
}

pub fn part2(input: &str) -> Answer {
    let mut brillo = vec![0u32; LADO * LADO];
    for (accion, x1, y1, x2, y2) in instrucciones(input) {
        for y in y1..=y2 {
            for b in &mut brillo[y * LADO + x1..=y * LADO + x2] {
                *b = match accion {
                    Accion::On => *b + 1,
                    Accion::Off => b.saturating_sub(1),
                    Accion::Toggle => *b + 2,
                };
            }
        }
    }
    Some(brillo.iter().map(|&b| b as u64).sum::<u64>().to_string())
}
