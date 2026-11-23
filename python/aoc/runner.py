"""Descubre y ejecuta los días de un año. Un día = un módulo y{año}/day{NN}.py."""
import importlib
import re
import sys
import time
from pathlib import Path

from .io import input_path, read_lines

BAR = "=" * 60


def available_days(year: int) -> list[int]:
    folder = Path(__file__).resolve().parents[1] / f"y{year}"
    return sorted(int(m.group(1)) for p in folder.glob("day*.py") if (m := re.fullmatch(r"day(\d+)\.py", p.name)))


def run_day(year: int, day: int, example: bool = False) -> bool:
    try:
        module = importlib.import_module(f"y{year}.day{day:02d}")
    except ModuleNotFoundError as e:
        if e.name and e.name.startswith(f"y{year}"):
            print(f"Día {day} no implementado para {year}")
            return False
        raise
    path = input_path(year, day, example)
    if not path.exists():
        print(f"No encuentro el input: {path}")
        return False

    lines = read_lines(year, day, example)
    print(f"\n{BAR}\n🎄 Advent of Code {year} - Día {day:02d}{' (ejemplo)' if example else ''} 🎄\n{BAR}")
    start = time.perf_counter()
    r1 = module.part1(lines)
    r2 = module.part2(lines)
    ms = (time.perf_counter() - start) * 1000
    print(f"Parte 1: {'-' if r1 is None else r1}")
    print(f"Parte 2: {'-' if r2 is None else r2}")
    print(f"Tiempo: {ms:.1f} ms")
    return True


def main(argv: list[str]) -> int:
    args = [a for a in argv if not a.startswith("--")]
    example = "--example" in argv
    if not args or not args[0].isdigit():
        print("Uso: python -m aoc <año> [día] [--example]")
        return 2
    year = int(args[0])
    if len(args) > 1:
        return 0 if run_day(year, int(args[1]), example) else 1

    days = available_days(year)
    if not days:
        print(f"No hay días para {year} (crea y{year}/dayNN.py con scripts/new_day.py)")
        return 1
    done = sum(run_day(year, d, example) for d in days)
    print(f"\n{BAR}\nADVENT OF CODE {year}: {done}/{len(days)} días ejecutados\n{BAR}")
    return 0
