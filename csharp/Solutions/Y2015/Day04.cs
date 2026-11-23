using System.Security.Cryptography;
using System.Text;
using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 4 (el input es la clave secreta: una sola línea de texto)
public class Day04 : Day
{
    // ¿El hash empieza por `ceros` dígitos hexadecimales a cero?
    private static bool EmpiezaPorCeros(byte[] hash, int ceros) =>
        Enumerable.Range(0, ceros).All(i => (i % 2 == 0 ? hash[i / 2] >> 4 : hash[i / 2] & 0x0f) == 0);

    private static int PrimerNumero(string clave, int ceros)
    {
        for (int n = 1; ; n++)
            if (EmpiezaPorCeros(MD5.HashData(Encoding.ASCII.GetBytes(clave + n)), ceros)) return n;
    }

    public override object? Part1(string[] lines) => PrimerNumero(lines[0].Trim(), 5);

    public override object? Part2(string[] lines) => PrimerNumero(lines[0].Trim(), 6);
}
