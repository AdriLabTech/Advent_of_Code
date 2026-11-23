using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 6
public class Day06 : Day
{
    private const int Lado = 1000;

    // Devuelve (accion, x1, y1, x2, y2) con x1<=x2 e y1<=y2.
    private static IEnumerable<(string Accion, int X1, int Y1, int X2, int Y2)> Instrucciones(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l =>
        {
            var accion = l.StartsWith("turn on") ? "on" : l.StartsWith("turn off") ? "off" : "toggle";
            var n = Input.Ints(l).Select(v => (int)v).ToArray();
            return (accion, Math.Min(n[0], n[2]), Math.Min(n[1], n[3]), Math.Max(n[0], n[2]), Math.Max(n[1], n[3]));
        });

    public override object? Part1(string[] lines)
    {
        var luces = new bool[Lado, Lado];
        foreach (var (accion, x1, y1, x2, y2) in Instrucciones(lines))
            for (int x = x1; x <= x2; x++)
                for (int y = y1; y <= y2; y++)
                    luces[x, y] = accion switch { "on" => true, "off" => false, _ => !luces[x, y] };
        return luces.Cast<bool>().Count(l => l);
    }

    public override object? Part2(string[] lines)
    {
        var brillo = new int[Lado, Lado];
        foreach (var (accion, x1, y1, x2, y2) in Instrucciones(lines))
            for (int x = x1; x <= x2; x++)
                for (int y = y1; y <= y2; y++)
                    brillo[x, y] = accion switch { "on" => brillo[x, y] + 1, "off" => Math.Max(0, brillo[x, y] - 1), _ => brillo[x, y] + 2 };
        return brillo.Cast<int>().Sum(b => (long)b);
    }
}
