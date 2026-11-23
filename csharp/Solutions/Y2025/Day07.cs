using System.Numerics;
using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 7
public class Day07 : Day
{
    private static (string[] Mapa, int Sy, int Sx) Leer(string[] lines)
    {
        var mapa = lines.Where(l => l.Length > 0).ToArray();
        int sy = Array.FindIndex(mapa, f => f.Contains('S'));
        return (mapa, sy, mapa[sy].IndexOf('S'));
    }

    public override object? Part1(string[] lines)
    {
        var (mapa, sy, sx) = Leer(lines);
        int ancho = mapa[0].Length, divisiones = 0;
        var rayos = new SortedSet<int> { sx };
        for (int y = sy; y < mapa.Length - 1; y++) // el rayo baja fila a fila
        {
            var siguiente = new SortedSet<int>();
            foreach (var x in rayos)
            {
                if (mapa[y + 1][x] == '^') // divisor: sale por los dos lados
                {
                    divisiones++;
                    if (x > 0) siguiente.Add(x - 1);
                    if (x < ancho - 1) siguiente.Add(x + 1);
                }
                else siguiente.Add(x);
            }
            rayos = siguiente;
        }
        return divisiones;
    }

    public override object? Part2(string[] lines)
    {
        var (mapa, sy, sx) = Leer(lines);
        int ancho = mapa[0].Length;
        // caminos[x]: líneas temporales que salen por abajo partiendo de (x, y); se rellena de abajo arriba
        var caminos = Enumerable.Repeat(BigInteger.One, ancho).ToArray();
        for (int y = mapa.Length - 2; y >= sy; y--)
        {
            var anterior = caminos;
            caminos = Enumerable.Range(0, ancho).Select(x =>
                mapa[y + 1][x] == '^'
                    ? (x > 0 ? anterior[x - 1] : 0) + (x < ancho - 1 ? anterior[x + 1] : 0)
                    : anterior[x]).ToArray();
        }
        return caminos[sx];
    }
}
