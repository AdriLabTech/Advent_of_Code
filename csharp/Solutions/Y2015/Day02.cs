using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 2
public class Day02 : Day
{
    // Cada línea 'AxBxC' como (a, b, c) con a <= b <= c.
    private static IEnumerable<(long A, long B, long C)> Cajas(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l =>
        {
            var d = l.Split('x').Select(long.Parse).Order().ToArray();
            return (d[0], d[1], d[2]);
        });

    // superficie total + el lado más pequeño (a*b) como holgura
    public override object? Part1(string[] lines) => Cajas(lines).Sum(c => 2 * (c.A * c.B + c.B * c.C + c.A * c.C) + c.A * c.B);

    // perímetro de la cara más pequeña + volumen
    public override object? Part2(string[] lines) => Cajas(lines).Sum(c => 2 * (c.A + c.B) + c.A * c.B * c.C);
}
