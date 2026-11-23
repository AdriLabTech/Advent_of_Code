using System.Text;
using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 10
public class Day10 : Day
{
    // Cada tanda de dígitos iguales se sustituye por (cuántos)(qué dígito).
    private static int MirarYDecir(string texto, int veces)
    {
        var actual = texto;
        for (int v = 0; v < veces; v++)
        {
            var siguiente = new StringBuilder(actual.Length * 2);
            for (int i = 0, j; i < actual.Length; i = j)
            {
                j = i;
                while (j < actual.Length && actual[j] == actual[i]) j++;
                siguiente.Append(j - i).Append(actual[i]);
            }
            actual = siguiente.ToString();
        }
        return actual.Length;
    }

    public override object? Part1(string[] lines) => MirarYDecir(lines[0].Trim(), 40);

    public override object? Part2(string[] lines) => MirarYDecir(lines[0].Trim(), 50);
}
