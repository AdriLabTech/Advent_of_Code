using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 21
public class Day21 : Day
{
    // (coste, daño, armadura) de la tienda
    private static readonly (int C, int D, int A)[] Armas = { (8, 4, 0), (10, 5, 0), (25, 6, 0), (40, 7, 0), (74, 8, 0) };
    private static readonly (int C, int D, int A)[] Armaduras = { (0, 0, 0), (13, 0, 1), (31, 0, 2), (53, 0, 3), (75, 0, 4), (102, 0, 5) }; // la primera = sin armadura
    private static readonly (int C, int D, int A)[] Anillos = { (25, 1, 0), (50, 2, 0), (100, 3, 0), (20, 0, 1), (40, 0, 2), (80, 0, 3) };

    // Gana quien tarda menos turnos en matar al otro (el jugador pega primero, así que gana en un empate).
    private static bool GanaJugador(int vida, int dano, int armadura, long[] jefe)
    {
        long turnosJugador = (jefe[0] + Math.Max(1, dano - jefe[2]) - 1) / Math.Max(1, dano - jefe[2]);
        long turnosJefe = (vida + Math.Max(1, jefe[1] - armadura) - 1) / Math.Max(1, jefe[1] - armadura);
        return turnosJugador <= turnosJefe;
    }

    // (coste, daño, armadura) de cada compra posible: 1 arma, 0-1 armadura y 0-2 anillos.
    private static IEnumerable<(int C, int D, int A)> Equipamientos()
    {
        var anillos = new List<(int C, int D, int A)[]> { Array.Empty<(int, int, int)>() };
        for (int i = 0; i < Anillos.Length; i++)
        {
            anillos.Add(new[] { Anillos[i] });
            for (int j = i + 1; j < Anillos.Length; j++) anillos.Add(new[] { Anillos[i], Anillos[j] });
        }
        foreach (var arma in Armas)
            foreach (var armadura in Armaduras)
                foreach (var par in anillos)
                    yield return (arma.C + armadura.C + par.Sum(a => a.C), arma.D + armadura.D + par.Sum(a => a.D), arma.A + armadura.A + par.Sum(a => a.A));
    }

    public override object? Part1(string[] lines)
    {
        var jefe = Input.Ints(string.Join(" ", lines));
        return Equipamientos().Where(e => GanaJugador(100, e.D, e.A, jefe)).Min(e => e.C);
    }

    public override object? Part2(string[] lines)
    {
        var jefe = Input.Ints(string.Join(" ", lines));
        return Equipamientos().Where(e => !GanaJugador(100, e.D, e.A, jefe)).Max(e => e.C);
    }
}
