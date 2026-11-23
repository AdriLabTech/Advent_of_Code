using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 1
public class Day01 : Day
{
    private const int Dial = 100; // posiciones del dial (0..99)
    private const int Start = 50; // posición inicial

    // Cada línea (L68, R48...) como desplazamiento con signo: L = negativo, R = positivo.
    private static IEnumerable<int> Rotations(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l))
             .Select(l => (l[0] == 'L' ? -1 : 1) * int.Parse(l.AsSpan(1)));

    // C# % puede dar negativos: se normaliza al rango 0..99.
    private static int Mod(int value) => ((value % Dial) + Dial) % Dial;

    public override object? Part1(string[] lines)
    {
        int pos = Start, zeros = 0;
        foreach (var delta in Rotations(lines))
        {
            pos = Mod(pos + delta);
            if (pos == 0) zeros++;
        }
        return zeros;
    }

    public override object? Part2(string[] lines)
    {
        int pos = Start, zeros = 0;
        foreach (var delta in Rotations(lines))
        {
            // Girar a la izquierda equivale a girar a la derecha desde la posición "espejo" (Dial - pos).
            // Así solo hay que contar cuántas veces se cruza un múltiplo de 100 hacia delante.
            int start = delta > 0 ? pos : Mod(Dial - pos);
            zeros += (start + Math.Abs(delta)) / Dial;
            pos = Mod(pos + delta);
        }
        return zeros;
    }
}
