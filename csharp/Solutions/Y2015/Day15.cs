using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 15
public class Day15 : Day
{
    private const int Cucharadas = 100;

    // Prueba todos los repartos de las cucharadas entre los ingredientes y devuelve la mejor puntuación.
    private static long MejorGalleta(string[] lines, long? calorias)
    {
        // capacidad, durabilidad, sabor, textura, calorías
        var ing = lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => Input.Ints(l.Split(':')[1])).ToArray();
        long mejor = 0;

        void Repartir(int i, int restantes, long[] propiedades)
        {
            if (i == ing.Length - 1) // el último ingrediente se lleva lo que queda
            {
                var p = Enumerable.Range(0, 5).Select(k => propiedades[k] + restantes * ing[i][k]).ToArray();
                if (calorias is null || calorias == p[4])
                    mejor = Math.Max(mejor, p.Take(4).Aggregate(1L, (a, v) => a * Math.Max(v, 0))); // un total negativo cuenta como 0
                return;
            }
            for (int cantidad = 0; cantidad <= restantes; cantidad++)
                Repartir(i + 1, restantes - cantidad, Enumerable.Range(0, 5).Select(k => propiedades[k] + cantidad * ing[i][k]).ToArray());
        }
        Repartir(0, Cucharadas, new long[5]);
        return mejor;
    }

    public override object? Part1(string[] lines) => MejorGalleta(lines, null);

    public override object? Part2(string[] lines) => MejorGalleta(lines, 500);
}
