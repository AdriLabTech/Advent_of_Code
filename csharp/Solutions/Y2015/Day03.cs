using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 3
public class Day03 : Day
{
    // Los repartidores se turnan: el movimiento i lo hace el repartidor i % repartidores.
    private static int CasasVisitadas(string ruta, int repartidores)
    {
        var posiciones = new (int X, int Y)[repartidores];
        var visitadas = new HashSet<(int, int)> { (0, 0) };
        for (int i = 0; i < ruta.Length; i++)
        {
            var (dx, dy) = ruta[i] switch { '^' => (0, 1), 'v' => (0, -1), '>' => (1, 0), '<' => (-1, 0), _ => (0, 0) };
            if (dx == 0 && dy == 0) continue;
            ref var p = ref posiciones[i % repartidores];
            p = (p.X + dx, p.Y + dy);
            visitadas.Add(p);
        }
        return visitadas.Count;
    }

    public override object? Part1(string[] lines) => CasasVisitadas(lines[0], 1);

    public override object? Part2(string[] lines) => CasasVisitadas(lines[0], 2);
}
