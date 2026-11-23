//! Helpers comunes: lectura de inputs y parsing.
use std::{env, fs, path::PathBuf};

/// Resultado de una parte: `None` = pendiente.
pub type Answer = Option<String>;

pub fn inputs_dir() -> PathBuf {
    env::var_os("AOC_INPUTS_DIR")
        .map(PathBuf::from)
        .unwrap_or_else(|| PathBuf::from(env!("CARGO_MANIFEST_DIR")).join("../inputs"))
}

pub fn input_path(year: u32, day: u32, example: bool) -> PathBuf {
    let suffix = if example { ".example" } else { "" };
    inputs_dir().join(year.to_string()).join(format!("day{day:02}{suffix}.txt"))
}

pub fn read_input(year: u32, day: u32, example: bool) -> std::io::Result<String> {
    fs::read_to_string(input_path(year, day, example))
}

/// Todos los enteros (con signo) que aparecen en un texto.
#[allow(dead_code)]
pub fn ints(text: &str) -> Vec<i64> {
    let mut out = Vec::new();
    let bytes = text.as_bytes();
    let mut i = 0;
    while i < bytes.len() {
        let neg = bytes[i] == b'-' && i + 1 < bytes.len() && bytes[i + 1].is_ascii_digit();
        if bytes[i].is_ascii_digit() || neg {
            let start = i;
            i += 1;
            while i < bytes.len() && bytes[i].is_ascii_digit() {
                i += 1;
            }
            out.push(text[start..i].parse().unwrap());
        } else {
            i += 1;
        }
    }
    out
}

/// Divide el texto en bloques separados por líneas en blanco.
#[allow(dead_code)]
pub fn paragraphs(text: &str) -> Vec<Vec<&str>> {
    let mut blocks = vec![Vec::new()];
    for line in text.lines() {
        if line.trim().is_empty() {
            if !blocks.last().unwrap().is_empty() {
                blocks.push(Vec::new());
            }
        } else {
            blocks.last_mut().unwrap().push(line);
        }
    }
    blocks.retain(|b| !b.is_empty());
    blocks
}
