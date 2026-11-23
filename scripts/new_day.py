#!/usr/bin/env python3
"""Genera el esqueleto de un día para uno o varios lenguajes.

Uso:  scripts/new_day.py <lenguaje|all> <año> <día>
      lenguajes: java python rust csharp cpp

Un día nuevo es un único fichero (dos en Java: Day + Utils, que además se registra solo).
Nunca sobrescribe ficheros existentes.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LANGS = ["java", "python", "rust", "csharp", "cpp"]


def render(tpl: Path, year: int, day: int) -> str:
    return (tpl.read_text(encoding="utf-8")
            .replace("{{YEAR}}", str(year))
            .replace("{{DAY}}", f"{day:02d}")
            .replace("{{DAYNUM}}", str(day)))


def write_new(path: Path, content: str) -> bool:
    if path.exists():
        print(f"  ya existe, no se toca: {path.relative_to(ROOT)}")
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content, encoding="utf-8")
    print(f"  creado: {path.relative_to(ROOT)}")
    return True


def simple(lang: str, tpl: str, target: str):
    def gen(year: int, day: int):
        write_new(ROOT / lang / target.format(y=year, d=f"{day:02d}"), render(ROOT / lang / "templates" / tpl, year, day))
    return gen


def java(year: int, day: int):
    base = ROOT / "java"
    t = base / "templates"
    dd = f"{day:02d}"
    write_new(base / f"src/year_{year}/Day_{dd}_{year}.java", render(t / "Day.java.tpl", year, day))
    write_new(base / f"src/utils_{year}/Utils_Day{dd}.java", render(t / "Utils.java.tpl", year, day))

    # Calendario del año (se crea si no existe) y registro del día
    cal = base / f"src/years/Year_{year}.java"
    write_new(cal, render(t / "Year.java.tpl", year, day))
    text = cal.read_text(encoding="utf-8")
    line = f"addDay({day}, new Day_{dd}_{year}());"
    if line not in text:
        text = re.sub(r"(protected void inicializeDays\(\) \{.*?)(\n    \}\n)", rf"\1\n        {line}\2", text, count=1, flags=re.S)
        cal.write_text(text, encoding="utf-8")
        print(f"  registrado en: {cal.relative_to(ROOT)}")

    # Main: import y case del año
    main = base / "src/core/Main.java"
    m = main.read_text(encoding="utf-8")
    if f"Year_{year}" not in m:
        m = m.replace("import years.Year_", f"import years.Year_{year};\nimport years.Year_", 1)
        m = re.sub(r"(switch \(year\) \{\n)", rf"\1\t\t\tcase {year}:\n\t\t\t\treturn new Year_{year}();\n", m, count=1)
        main.write_text(m, encoding="utf-8")
        print(f"  año {year} añadido en: {main.relative_to(ROOT)}")


GENERATORS = {
    "java": java,
    "python": simple("python", "day.py.tpl", "y{y}/day{d}.py"),
    "rust": simple("rust", "day.rs.tpl", "src/solutions/y{y}/day{d}.rs"),
    "csharp": simple("csharp", "Day.cs.tpl", "Solutions/Y{y}/Day{d}.cs"),
    "cpp": simple("cpp", "day.cpp.tpl", "src/solutions/y{y}/day{d}.cpp"),
}


def main(argv: list[str]) -> int:
    if len(argv) != 3 or argv[0] not in LANGS + ["all"] or not (argv[1].isdigit() and argv[2].isdigit()):
        print(__doc__)
        return 2
    year, day = int(argv[1]), int(argv[2])
    if not (2015 <= year <= 2099 and 1 <= day <= 25):
        print("Año (2015+) o día (1-25) fuera de rango")
        return 2
    for lang in (LANGS if argv[0] == "all" else [argv[0]]):
        print(lang)
        GENERATORS[lang](year, day)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
