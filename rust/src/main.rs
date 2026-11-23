mod aoc;

use aoc::Answer;
use std::time::Instant;

pub struct Day {
    pub year: u32,
    pub day: u32,
    pub part1: fn(&str) -> Answer,
    pub part2: fn(&str) -> Answer,
}

// Registro generado por build.rs a partir de src/solutions/y*/day*.rs
include!(concat!(env!("OUT_DIR"), "/registry.rs"));

const BAR: &str = "============================================================";

fn run_day(d: &Day, example: bool) -> bool {
    let path = aoc::input_path(d.year, d.day, example);
    let Ok(input) = aoc::read_input(d.year, d.day, example) else {
        println!("No encuentro el input: {}", path.display());
        return false;
    };
    println!("\n{BAR}\n🎄 Advent of Code {} - Día {:02}{} 🎄\n{BAR}", d.year, d.day, if example { " (ejemplo)" } else { "" });
    let start = Instant::now();
    let r1 = (d.part1)(&input);
    let r2 = (d.part2)(&input);
    let ms = start.elapsed().as_secs_f64() * 1000.0;
    println!("Parte 1: {}", r1.as_deref().unwrap_or("-"));
    println!("Parte 2: {}", r2.as_deref().unwrap_or("-"));
    println!("Tiempo: {ms:.1} ms");
    true
}

fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let example = args.iter().any(|a| a == "--example");
    let nums: Vec<u32> = args.iter().filter_map(|a| a.parse().ok()).collect();
    let Some(&year) = nums.first() else {
        eprintln!("Uso: cargo run --release -- <año> [día] [--example]");
        std::process::exit(2);
    };
    let days: Vec<&Day> = DAYS.iter().filter(|d| d.year == year && nums.get(1).is_none_or(|&n| n == d.day)).collect();
    if days.is_empty() {
        println!("No hay días implementados para ese año/día (crea uno con scripts/new_day.py)");
        std::process::exit(1);
    }
    let done = days.iter().filter(|d| run_day(d, example)).count();
    if nums.len() == 1 {
        println!("\n{BAR}\nADVENT OF CODE {year}: {done}/{} días ejecutados\n{BAR}", days.len());
    }
    if done == 0 {
        std::process::exit(1);
    }
}
