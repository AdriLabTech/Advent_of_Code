using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 16
public class Day16 : Day
{
    private static readonly Dictionary<string, int> Huella = new()
    {
        ["children"] = 3, ["cats"] = 7, ["samoyeds"] = 2, ["pomeranians"] = 3, ["akitas"] = 0,
        ["vizslas"] = 0, ["goldfish"] = 5, ["trees"] = 3, ["cars"] = 2, ["perfumes"] = 1,
    };

    // (número, {compuesto: cantidad}) de cada línea 'Sue 1: goldfish: 6, trees: 9, ...'.
    private static IEnumerable<(int Numero, Dictionary<string, int> Recuerdos)> Tias(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l =>
        {
            int dosPuntos = l.IndexOf(':');
            var recuerdos = l[(dosPuntos + 1)..].Split(',').Select(p => p.Split(':')).ToDictionary(p => p[0].Trim(), p => int.Parse(p[1]));
            return (int.Parse(l[4..dosPuntos]), recuerdos);
        });

    // La tía cuyos recuerdos cumplen `orden(compuesto)` (el signo que debe tener su valor menos la huella).
    private static int Buscar(string[] lines, Func<string, int> orden) =>
        Tias(lines).First(t => t.Recuerdos.All(r => Math.Sign(r.Value.CompareTo(Huella[r.Key])) == orden(r.Key))).Numero;

    public override object? Part1(string[] lines) => Buscar(lines, _ => 0);

    // cats y trees: mayor que la huella; pomeranians y goldfish: menor
    public override object? Part2(string[] lines) =>
        Buscar(lines, k => k is "cats" or "trees" ? 1 : k is "pomeranians" or "goldfish" ? -1 : 0);
}
