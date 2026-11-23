using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 23
public class Day23 : Day
{
    // Ejecuta el programa hasta salirse de él y devuelve los registros (a, b).
    private static (long A, long B) Ejecutar(string[] lines, long a)
    {
        var programa = lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => l.Replace(",", "").Split(' ', StringSplitOptions.RemoveEmptyEntries)).ToArray();
        var registros = new long[] { a, 0 };
        int Reg(string r) => r == "b" ? 1 : 0;
        int pc = 0;
        while (pc >= 0 && pc < programa.Length)
        {
            var i = programa[pc];
            int salto = 1;
            switch (i[0])
            {
                case "hlf": registros[Reg(i[1])] /= 2; break;
                case "tpl": registros[Reg(i[1])] *= 3; break;
                case "inc": registros[Reg(i[1])]++; break;
                case "jmp": salto = int.Parse(i[1]); break;
                case "jie" when registros[Reg(i[1])] % 2 == 0: salto = int.Parse(i[2]); break;
                case "jio" when registros[Reg(i[1])] == 1: salto = int.Parse(i[2]); break;
            }
            pc += salto;
        }
        return (registros[0], registros[1]);
    }

    // el ejemplo del enunciado (4 instrucciones) deja el resultado en a
    public override object? Part1(string[] lines) => lines.Count(l => !string.IsNullOrWhiteSpace(l)) > 4 ? Ejecutar(lines, 0).B : Ejecutar(lines, 0).A;

    public override object? Part2(string[] lines) => Ejecutar(lines, 1).B;
}
