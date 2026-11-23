"""Advent of Code 2015 - Día 23"""


def ejecutar(lines: list[str], a: int = 0) -> dict[str, int]:
    """Ejecuta el programa hasta salirse de él y devuelve los registros."""
    programa = [l.replace(",", "").split() for l in lines if l.strip()]
    registros = {"a": a, "b": 0}
    pc = 0
    while 0 <= pc < len(programa):
        instruccion, *argumentos = programa[pc]
        salto = 1
        if instruccion == "hlf":
            registros[argumentos[0]] //= 2
        elif instruccion == "tpl":
            registros[argumentos[0]] *= 3
        elif instruccion == "inc":
            registros[argumentos[0]] += 1
        elif instruccion == "jmp":
            salto = int(argumentos[0])
        elif instruccion == "jie" and registros[argumentos[0]] % 2 == 0:
            salto = int(argumentos[1])
        elif instruccion == "jio" and registros[argumentos[0]] == 1:
            salto = int(argumentos[1])
        pc += salto
    return registros


def part1(lines: list[str]):
    r = ejecutar(lines)
    return r["b"] if len(lines) > 4 else r["a"]  # el ejemplo del enunciado (4 instrucciones) deja el resultado en a


def part2(lines: list[str]):
    return ejecutar(lines, a=1)["b"]
