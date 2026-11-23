using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 8
public class Day08 : Day
{
    // Caracteres del valor de un literal: cada escape (\\, \", \xNN) cuenta como uno; las comillas exteriores no cuentan.
    private static int EnMemoria(string literal)
    {
        var c = literal[1..^1];
        int i = 0, n = 0;
        while (i < c.Length)
        {
            i += c[i] == '\\' ? (c[i + 1] == 'x' ? 4 : 2) : 1;
            n++;
        }
        return n;
    }

    // Caracteres de la cadena codificada de nuevo: comillas exteriores y \ y " escapadas.
    private static int Codificado(string literal) => literal.Length + 2 + literal.Count(ch => ch is '\\' or '"');

    private static IEnumerable<string> Literales(string[] lines) => lines.Select(l => l.Trim()).Where(l => l.Length > 0);

    public override object? Part1(string[] lines) => Literales(lines).Sum(l => l.Length - EnMemoria(l));

    public override object? Part2(string[] lines) => Literales(lines).Sum(l => Codificado(l) - l.Length);
}
