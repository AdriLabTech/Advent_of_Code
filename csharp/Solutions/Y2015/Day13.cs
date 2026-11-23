using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 13
public class Day13 : Day
{
    // 'A would gain/lose N happiness units by sitting next to B.' -> felicidad[(A, B)]
    private static Dictionary<(string, string), int> Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => l.TrimEnd('.').Split(' '))
             .ToDictionary(p => (p[0], p[^1]), p => int.Parse(p[3]) * (p[2] == "gain" ? 1 : -1));

    // Mayor suma de felicidad en una mesa redonda (cada pareja de vecinos cuenta en los dos sentidos).
    private static int MejorMesa(Dictionary<(string, string), int> f, List<string> invitados)
    {
        invitados.Sort(StringComparer.Ordinal);
        int Valor(int a, int b) => f.GetValueOrDefault((invitados[a], invitados[b])) + f.GetValueOrDefault((invitados[b], invitados[a]));
        var mesa = Enumerable.Range(0, invitados.Count).ToArray();
        int mejor = int.MinValue;
        void Permutar(int desde)
        {
            if (desde == mesa.Length)
            {
                int total = 0;
                for (int i = 0; i < mesa.Length; i++) total += Valor(mesa[i], mesa[(i + 1) % mesa.Length]);
                mejor = Math.Max(mejor, total);
                return;
            }
            for (int i = desde; i < mesa.Length; i++)
            {
                (mesa[desde], mesa[i]) = (mesa[i], mesa[desde]);
                Permutar(desde + 1);
                (mesa[desde], mesa[i]) = (mesa[i], mesa[desde]);
            }
        }
        Permutar(1); // la mesa es circular: fijar el primero evita repetir giros
        return mejor;
    }

    public override object? Part1(string[] lines)
    {
        var f = Leer(lines);
        return MejorMesa(f, f.Keys.Select(k => k.Item1).Distinct().ToList());
    }

    public override object? Part2(string[] lines)
    {
        var f = Leer(lines);
        var invitados = f.Keys.Select(k => k.Item1).Distinct().ToList();
        invitados.Add("Yo"); // yo me siento con felicidad 0 con todos
        return MejorMesa(f, invitados);
    }
}
