using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 11
public class Day11 : Day
{
    private static readonly string[] Obligatorios = { "dac", "fft" };

    private static Dictionary<string, string[]> Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l))
             .Select(l => l.Split(':'))
             .ToDictionary(p => p[0].Trim(), p => p.Length > 1 ? p[1].Split(' ', StringSplitOptions.RemoveEmptyEntries) : Array.Empty<string>());

    public override object? Part1(string[] lines)
    {
        var grafo = Leer(lines);
        var memo = new Dictionary<string, long>();

        long Caminos(string nodo)
        {
            if (nodo == "out") return 1;
            if (memo.TryGetValue(nodo, out var m)) return m;
            long total = grafo.GetValueOrDefault(nodo, []).Sum(Caminos);
            return memo[nodo] = total;
        }

        return Caminos("you");
    }

    public override object? Part2(string[] lines)
    {
        var grafo = Leer(lines);
        var memo = new Dictionary<(string, int), long>();

        // pendientes es una máscara de bits con los obligatorios que aún no se han visitado
        long Caminos(string nodo, int pendientes)
        {
            if (nodo == "out") return pendientes == 0 ? 1 : 0; // solo vale si pasó por todos los obligatorios
            if (memo.TryGetValue((nodo, pendientes), out var m)) return m;
            int i = Array.IndexOf(Obligatorios, nodo);
            int ahora = i >= 0 ? pendientes & ~(1 << i) : pendientes;
            long total = grafo.GetValueOrDefault(nodo, []).Sum(s => Caminos(s, ahora));
            return memo[(nodo, pendientes)] = total;
        }

        return Caminos("svr", (1 << Obligatorios.Length) - 1);
    }
}
