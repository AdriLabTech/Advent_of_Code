using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 17
public class Day17 : Day
{
    private const int Litros = 150;
    private const int LitrosEjemplo = 25; // el ejemplo del enunciado (5 contenedores) guarda 25 litros

    // formas[n] = de cuántas maneras se llenan exactamente los litros con n contenedores (programación dinámica).
    private static long[] FormasPorCantidad(string[] lines)
    {
        var contenedores = lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(int.Parse).ToArray();
        int litros = contenedores.Length <= 5 ? LitrosEjemplo : Litros;
        // tabla[n, s]: subconjuntos de n contenedores que suman s litros
        var tabla = new long[contenedores.Length + 1, litros + 1];
        tabla[0, 0] = 1;
        foreach (var c in contenedores)
            for (int n = contenedores.Length - 1; n >= 0; n--)
                for (int s = litros - c; s >= 0; s--)
                    tabla[n + 1, s + c] += tabla[n, s];
        return Enumerable.Range(0, contenedores.Length + 1).Select(n => tabla[n, litros]).ToArray();
    }

    public override object? Part1(string[] lines) => FormasPorCantidad(lines).Sum();

    // formas con el menor número posible de contenedores
    public override object? Part2(string[] lines) => FormasPorCantidad(lines).First(f => f > 0);
}
