//! Descubre src/solutions/y{año}/day{NN}.rs y genera el registro de días.
//! Así un día nuevo = un fichero nuevo, sin tocar mod.rs ni main.rs.
use std::{env, fs, path::PathBuf};

fn main() {
    let root = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap()).join("src/solutions");
    println!("cargo:rerun-if-changed={}", root.display());

    let mut days: Vec<(u32, u32, PathBuf)> = Vec::new();
    if let Ok(years) = fs::read_dir(&root) {
        for y in years.flatten() {
            let ystr = y.file_name().to_string_lossy().to_string();
            let Some(year) = ystr.strip_prefix('y').and_then(|s| s.parse::<u32>().ok()) else { continue };
            for d in fs::read_dir(y.path()).into_iter().flatten().flatten() {
                let fname = d.file_name().to_string_lossy().to_string();
                let Some(day) = fname.strip_prefix("day").and_then(|s| s.strip_suffix(".rs")).and_then(|s| s.parse::<u32>().ok()) else { continue };
                days.push((year, day, d.path()));
            }
        }
    }
    days.sort();

    let mut out = String::new();
    for (y, d, p) in &days {
        out += &format!("#[path = {:?}]\nmod y{y}_day{d:02};\n", p.display().to_string());
    }
    out += "pub const DAYS: &[Day] = &[\n";
    for (y, d, _) in &days {
        out += &format!("    Day {{ year: {y}, day: {d}, part1: y{y}_day{d:02}::part1, part2: y{y}_day{d:02}::part2 }},\n");
    }
    out += "];\n";
    fs::write(PathBuf::from(env::var("OUT_DIR").unwrap()).join("registry.rs"), out).unwrap();
}
