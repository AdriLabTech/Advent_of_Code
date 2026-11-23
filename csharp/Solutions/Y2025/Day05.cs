using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 5
public class Day05 : Day
{
    // Rangos frescos 'a-b', línea en blanco y luego los IDs disponibles.
    private static (List<(long A, long B)> Rangos, List<long> Ids) Leer(string[] lines)
    {
        var rangos = new List<(long, long)>();
        var ids = new List<long>();
        bool enRangos = true;
        foreach (var line in lines)
        {
            if (string.IsNullOrWhiteSpace(line)) enRangos = false;
            else if (enRangos)
            {
                var p = line.Split('-');
                rangos.Add((long.Parse(p[0]), long.Parse(p[1])));
            }
            else ids.Add(long.Parse(line.Trim()));
        }
        return (rangos, ids);
    }

    public override object? Part1(string[] lines)
    {
        var (rangos, ids) = Leer(lines);
        return ids.Count(i => rangos.Any(r => r.A <= i && i <= r.B));
    }

    public override object? Part2(string[] lines)
    {
        // unión de rangos: se ordenan y se fusionan los que se solapan o se tocan; luego se suman sus longitudes
        long total = 0, hasta = -1;
        foreach (var (a, b) in Leer(lines).Rangos.OrderBy(r => r.A).ThenBy(r => r.B))
            if (b > hasta)
            {
                total += b - Math.Max(a, hasta + 1) + 1;
                hasta = b;
            }
        return total;
    }
}
