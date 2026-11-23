# 🦀 Rust

Estilo: **funciones libres + registro generado en compilación**. `build.rs` escanea `src/solutions/y*/day*.rs` y genera el registro, así que un día nuevo es un fichero y no hay que tocar `mod` ni `main.rs`.

Requisitos: Rust estable (edición 2024), cargo. Sin dependencias externas.

```
rust/
├── Cargo.toml
├── build.rs                 # genera el registro de días
├── src/
│   ├── main.rs              # CLI y ejecutor
│   ├── aoc.rs               # read_input, ints, paragraphs, tipo Answer
│   └── solutions/y2025/day01.rs   # una solución = un fichero
└── templates/day.rs.tpl
```

## Crear un día
```bash
scripts/new_day.py rust 2025 3       # desde la raíz del repo
```
Edita `part1(input: &str) -> Answer` y `part2`. Devuelve `Some(resultado.to_string())` (`None` = pendiente).

## Ejecutar (desde `rust/`)
```bash
cargo run --release -- 2025 3
cargo run --release -- 2025             # todo el año
cargo run --release -- 2025 3 --example
```
