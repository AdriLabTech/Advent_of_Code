# Rust

Estado: **sin empezar** (estructura preparada, ningún día resuelto).

Sigue el contrato de [../docs/CONVENCIONES.md](../docs/CONVENCIONES.md):

- Input: `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). No se versiona.
- Cada día expone `part1` y `part2` y devuelve texto.
- Ejecutor por año/día con tiempo de ejecución.

## Requisitos
- Rust estable (rustup), cargo

## Estructura sugerida
```
rust/
├── Cargo.toml      # workspace o crate único
└── src/y2025/day01.rs
```
Ejecución prevista: `cargo run --release -- 2025 1`
