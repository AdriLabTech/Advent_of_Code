using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 4
public class Day04 : Day
{
    private static readonly (int Dr, int Dc)[] Vecinos = { (-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1) };

    private static HashSet<(int R, int C)> LeerRollos(string[] lines) =>
        lines.SelectMany((line, r) => line.Select((ch, c) => (ch, r, c))).Where(t => t.ch == '@').Select(t => (t.r, t.c)).ToHashSet();

    // Rollos con menos de 4 rollos vecinos.
    private static List<(int R, int C)> Accesibles(HashSet<(int R, int C)> rollos) =>
        rollos.Where(p => Vecinos.Count(v => rollos.Contains((p.R + v.Dr, p.C + v.Dc))) < 4).ToList();

    public override object? Part1(string[] lines) => Accesibles(LeerRollos(lines)).Count;

    public override object? Part2(string[] lines)
    {
        var rollos = LeerRollos(lines);
        int quitados = 0;
        List<(int R, int C)> retirar;
        while ((retirar = Accesibles(rollos)).Count > 0) // se repite hasta que no quede ninguno accesible
        {
            rollos.ExceptWith(retirar);
            quitados += retirar.Count;
        }
        return quitados;
    }
}
