using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 1
public class Day01 : Day
{
    private static int Paso(int piso, char c) => c switch { '(' => piso + 1, ')' => piso - 1, _ => piso };

    public override object? Part1(string[] lines) => lines[0].Aggregate(0, Paso);

    // Posición (empezando en 1) del primer carácter que lleva al piso -1.
    public override object? Part2(string[] lines)
    {
        int piso = 0;
        for (int i = 0; i < lines[0].Length; i++)
        {
            piso = Paso(piso, lines[0][i]);
            if (piso == -1) return i + 1;
        }
        return null; // nunca entra en el sótano
    }
}
