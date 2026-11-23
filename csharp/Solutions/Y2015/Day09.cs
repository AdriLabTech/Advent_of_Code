using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 9
public class Day09 : Day
{
    // (ruta más corta, ruta más larga) que visitan todas las ciudades exactamente una vez (hay pocas: se prueban todas).
    private static (int Min, int Max) Rutas(string[] lines)
    {
        var ids = new Dictionary<string, int>();
        int Id(string c) => ids.TryGetValue(c, out var i) ? i : ids[c] = ids.Count;
        var tramos = new List<(int A, int B, int D)>();
        foreach (var l in lines.Where(l => !string.IsNullOrWhiteSpace(l)))
        {
            var p = l.Split(" = ");
            var ciudades = p[0].Split(" to ");
            tramos.Add((Id(ciudades[0]), Id(ciudades[1]), int.Parse(p[1])));
        }
        int n = ids.Count;
        var d = new int[n, n];
        foreach (var (a, b, v) in tramos) d[a, b] = d[b, a] = v;

        int min = int.MaxValue, max = 0;
        void Recorrer(int actual, int visitadas, int recorrido)
        {
            if (int.PopCount(visitadas) == n) { min = Math.Min(min, recorrido); max = Math.Max(max, recorrido); return; }
            for (int s = 0; s < n; s++)
                if ((visitadas >> s & 1) == 0) Recorrer(s, visitadas | 1 << s, recorrido + d[actual, s]);
        }
        for (int inicio = 0; inicio < n; inicio++) Recorrer(inicio, 1 << inicio, 0);
        return (min, max);
    }

    public override object? Part1(string[] lines) => Rutas(lines).Min;

    public override object? Part2(string[] lines) => Rutas(lines).Max;
}
