using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 11
public class Day11 : Day
{
    private const string Prohibidas = "iol";

    // Suma uno como si fuera un número en base 26 (z pasa a a y acarrea). Salta de golpe las que tienen i, o o l.
    private static void Incrementar(char[] clave)
    {
        int i = Array.FindIndex(clave, c => Prohibidas.Contains(c));
        if (i >= 0) // si ya hay una letra prohibida, todo lo que va detrás se pone a 'a'
        {
            clave[i]++;
            for (int k = i + 1; k < clave.Length; k++) clave[k] = 'a';
            return;
        }
        for (int k = clave.Length - 1; k >= 0; k--)
        {
            if (clave[k] == 'z') clave[k] = 'a';
            else { clave[k]++; break; }
        }
    }

    private static bool EsValida(char[] c)
    {
        bool escalera = Enumerable.Range(0, c.Length - 2).Any(i => c[i] + 1 == c[i + 1] && c[i + 1] + 1 == c[i + 2]);
        bool sinProhibidas = !c.Any(ch => Prohibidas.Contains(ch));
        int dobles = Enumerable.Range(0, c.Length - 1).Where(i => c[i] == c[i + 1]).Select(i => c[i]).Distinct().Count(); // letras distintas dobles
        return escalera && sinProhibidas && dobles >= 2;
    }

    private static string SiguienteClave(string clave)
    {
        var c = clave.ToCharArray();
        do Incrementar(c); while (!EsValida(c));
        return new string(c);
    }

    public override object? Part1(string[] lines) => SiguienteClave(lines[0].Trim());

    public override object? Part2(string[] lines) => SiguienteClave(SiguienteClave(lines[0].Trim()));
}
