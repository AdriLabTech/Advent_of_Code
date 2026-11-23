"""Lectura de inputs y pequeños helpers de parsing."""
import os
import re
from pathlib import Path

# python/aoc/io.py -> raíz del repositorio = parents[2]
REPO_ROOT = Path(__file__).resolve().parents[2]


def inputs_dir() -> Path:
    return Path(os.environ.get("AOC_INPUTS_DIR", REPO_ROOT / "inputs"))


def input_path(year: int, day: int, example: bool = False) -> Path:
    suffix = ".example" if example else ""
    return inputs_dir() / str(year) / f"day{day:02d}{suffix}.txt"


def read_text(year: int, day: int, example: bool = False) -> str:
    return input_path(year, day, example).read_text(encoding="utf-8")


def read_lines(year: int, day: int, example: bool = False) -> list[str]:
    return read_text(year, day, example).splitlines()


def ints(text: str) -> list[int]:
    """Todos los enteros (con signo) que aparecen en un texto."""
    return [int(x) for x in re.findall(r"-?\d+", text)]


def paragraphs(lines: list[str]) -> list[list[str]]:
    """Divide una lista de líneas en bloques separados por líneas en blanco."""
    blocks: list[list[str]] = [[]]
    for line in lines:
        if line.strip():
            blocks[-1].append(line)
        elif blocks[-1]:
            blocks.append([])
    return [b for b in blocks if b]
