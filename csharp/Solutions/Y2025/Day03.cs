using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 3
public class Day03 : Day
{
    // Número más grande que se forma encendiendo `cuantas` baterías sin cambiar su orden (voraz).
    private static long MayorJoltaje(string banco, int cuantas)
    {
        var elegidas = new List<char>();
        for (int i = 0; i < banco.Length; i++)
        {
            // una elegida peor que la actual se descarta mientras queden baterías de sobra para completar el número
            while (elegidas.Count > 0 && elegidas[^1] < banco[i] && elegidas.Count + banco.Length - i > cuantas)
                elegidas.RemoveAt(elegidas.Count - 1);
            if (elegidas.Count < cuantas) elegidas.Add(banco[i]);
        }
        return long.Parse(new string(elegidas.ToArray()));
    }

    private static long Total(string[] lines, int cuantas) =>
        lines.Select(l => l.Trim()).Where(l => l.Length > 0).Sum(l => MayorJoltaje(l, cuantas));

    public override object? Part1(string[] lines) => Total(lines, 2);

    public override object? Part2(string[] lines) => Total(lines, 12);
}
