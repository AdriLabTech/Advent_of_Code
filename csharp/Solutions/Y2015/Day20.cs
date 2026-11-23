using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 20 (el input es un número en una línea)
public class Day20 : Day
{
    // regalos[c] = presentes que recibe la casa c (criba: cada elfo recorre sus casas) hasta la casa `limite`.
    private static long[] Regalos(int limite, int porElfo, int? casasPorElfo)
    {
        var casas = new long[limite + 1];
        for (int elfo = 1; elfo <= limite; elfo++)
        {
            long ultima = casasPorElfo is { } n ? Math.Min(limite, (long)elfo * n) : limite;
            for (long casa = elfo; casa <= ultima; casa += elfo) casas[casa] += (long)porElfo * elfo;
        }
        return casas;
    }

    private static int PrimeraCasa(long objetivo, int porElfo, int? casasPorElfo)
    {
        for (int limite = 1 << 14; ; limite *= 2) // si no aparece, se duplica el rango y se vuelve a cribar
        {
            var casas = Regalos(limite, porElfo, casasPorElfo);
            int i = Array.FindIndex(casas, t => t >= objetivo);
            if (i >= 0) return i;
        }
    }

    public override object? Part1(string[] lines) => PrimeraCasa(long.Parse(lines[0]), 10, null);

    // cada elfo reparte 11 veces su número y solo a 50 casas
    public override object? Part2(string[] lines) => PrimeraCasa(long.Parse(lines[0]), 11, 50);
}
