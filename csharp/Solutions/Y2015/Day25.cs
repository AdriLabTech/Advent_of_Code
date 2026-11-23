using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 25 (el input es 'Enter the code at row R, column C.')
public class Day25 : Day
{
    private const long PrimerCodigo = 20151125, Multiplicador = 252533, Modulo = 33554393;

    // Código de la casilla (fila, columna): el papel se rellena por diagonales, así que primero se halla el
    // número de orden n de la casilla y luego se aplica n-1 veces el generador (con potencia modular, sin bucle).
    private static long Codigo(long fila, long columna)
    {
        long diagonal = fila + columna - 1; // las diagonales anteriores contienen 1 + 2 + ... + (diagonal-1) casillas
        long n = (diagonal - 1) * diagonal / 2 + columna;
        long baseP = Multiplicador, exponente = n - 1, resultado = 1;
        for (; exponente > 0; exponente >>= 1, baseP = baseP * baseP % Modulo)
            if ((exponente & 1) == 1) resultado = resultado * baseP % Modulo;
        return PrimerCodigo * resultado % Modulo;
    }

    public override object? Part1(string[] lines)
    {
        var n = Input.Ints(lines[0]);
        return Codigo(n[0], n[1]);
    }

    public override object? Part2(string[] lines) => null; // la parte 2 es la estrella final gratuita (no tiene puzzle)
}
