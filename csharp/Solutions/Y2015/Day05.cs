using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 5
public class Day05 : Day
{
    private static bool EsBuenaV1(string s)
    {
        bool vocales = s.Count(c => "aeiou".Contains(c)) >= 3;
        bool doble = s.Zip(s.Skip(1)).Any(p => p.First == p.Second);
        bool prohibida = new[] { "ab", "cd", "pq", "xy" }.Any(s.Contains);
        return vocales && doble && !prohibida;
    }

    private static bool EsBuenaV2(string s)
    {
        // un par de letras que reaparece más adelante sin solaparse
        bool parRepetido = Enumerable.Range(0, Math.Max(0, s.Length - 1)).Any(i => s.IndexOf(s.Substring(i, 2), i + 2, StringComparison.Ordinal) != -1);
        // una letra que se repite con otra en medio (xyx)
        bool letraEntre = Enumerable.Range(0, Math.Max(0, s.Length - 2)).Any(i => s[i] == s[i + 2]);
        return parRepetido && letraEntre;
    }

    public override object? Part1(string[] lines) => lines.Count(EsBuenaV1);

    public override object? Part2(string[] lines) => lines.Count(EsBuenaV2);
}
