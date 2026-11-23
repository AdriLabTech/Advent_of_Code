using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 7
public class Day07 : Day
{
    private static Dictionary<string, string[]> Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l))
             .Select(l => l.Split(" -> "))
             .ToDictionary(p => p[1].Trim(), p => p[0].Split(' ', StringSplitOptions.RemoveEmptyEntries));

    // Señal de un cable (o número). `forzado` sustituye la señal de un cable.
    private static ushort Valor(string token, Dictionary<string, string[]> gates, Dictionary<string, ushort> memo, (string Cable, ushort Valor)? forzado)
    {
        if (ushort.TryParse(token, out var n)) return n;
        if (forzado is { } f && f.Cable == token) return f.Valor;
        if (memo.TryGetValue(token, out var m)) return m;
        var g = gates[token];
        ushort resultado = g.Length switch
        {
            1 => Valor(g[0], gates, memo, forzado),                       // 123 -> x  /  a -> b
            2 => (ushort)~Valor(g[1], gates, memo, forzado),              // NOT x
            _ => g[1] switch
            {
                "AND" => (ushort)(Valor(g[0], gates, memo, forzado) & Valor(g[2], gates, memo, forzado)),
                "OR" => (ushort)(Valor(g[0], gates, memo, forzado) | Valor(g[2], gates, memo, forzado)),
                "LSHIFT" => (ushort)(Valor(g[0], gates, memo, forzado) << Valor(g[2], gates, memo, forzado)),
                _ => (ushort)(Valor(g[0], gates, memo, forzado) >> Valor(g[2], gates, memo, forzado)), // RSHIFT
            },
        };
        return memo[token] = resultado;
    }

    // el ejemplo del enunciado no tiene cable a
    public override object? Part1(string[] lines)
    {
        var gates = Leer(lines);
        return gates.ContainsKey("a") ? Valor("a", gates, new(), null) : null;
    }

    // la señal de a (parte 1) se pasa al cable b y se recalcula todo
    public override object? Part2(string[] lines)
    {
        var gates = Leer(lines);
        if (!gates.ContainsKey("a")) return null;
        ushort a = Valor("a", gates, new(), null);
        return Valor("a", gates, new(), ("b", a));
    }
}
