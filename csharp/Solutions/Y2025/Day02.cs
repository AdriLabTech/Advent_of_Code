using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 2
public class Day02 : Day
{
    // Líneas 'a-b,c-d,...' como lista de (a, b).
    private static List<(Int128 A, Int128 B)> Rangos(string[] lines) =>
        lines.SelectMany(l => l.Split(','))
             .Select(r => r.Trim())
             .Where(r => r.Length > 0)
             .Select(r => r.Split('-'))
             .Select(p => (Int128.Parse(p[0]), Int128.Parse(p[1])))
             .ToList();

    private static Int128 Diez(int potencia)
    {
        Int128 v = 1;
        for (int i = 0; i < potencia; i++) v *= 10;
        return v;
    }

    // Suma de los números de `largo` dígitos en [a, b] formados repitiendo un bloque de `periodo` dígitos.
    private static Int128 SumaConPeriodo(Int128 a, Int128 b, int largo, int periodo)
    {
        a = Int128.Max(a, Diez(largo - 1));
        b = Int128.Min(b, Diez(largo) - 1);
        Int128 m = (Diez(largo) - 1) / (Diez(periodo) - 1); // n = x * m con x de `periodo` dígitos
        Int128 menor = Int128.Max(Diez(periodo - 1), (a + m - 1) / m);
        Int128 mayor = Int128.Min(Diez(periodo) - 1, b / m);
        return menor <= mayor ? m * (menor + mayor) * (mayor - menor + 1) / 2 : 0;
    }

    public override object? Part1(string[] lines)
    {
        // ID inválido = un bloque repetido exactamente dos veces: periodo = mitad de los dígitos
        Int128 total = 0;
        foreach (var (a, b) in Rangos(lines))
            for (int largo = 2; largo <= b.ToString().Length; largo += 2)
                total += SumaConPeriodo(a, b, largo, largo / 2);
        return total;
    }

    public override object? Part2(string[] lines)
    {
        // ahora vale cualquier número de repeticiones (>= 2): un periodo p < largo que divida al largo.
        // Un mismo número puede tener varios periodos (111111 -> 1, 2 y 3), así que se suma por periodo
        // mínimo exacto: g[p] = (números con periodo p) - (los que ya tienen un periodo menor que divide a p)
        Int128 total = 0;
        foreach (var (a, b) in Rangos(lines))
            for (int largo = 2; largo <= b.ToString().Length; largo++)
            {
                var g = new List<(int Periodo, Int128 Suma)>();
                for (int p = 1; p < largo; p++)
                    if (largo % p == 0)
                    {
                        Int128 yaContados = g.Where(x => p % x.Periodo == 0).Aggregate((Int128)0, (s, x) => s + x.Suma);
                        g.Add((p, SumaConPeriodo(a, b, largo, p) - yaContados));
                    }
                total += g.Aggregate((Int128)0, (s, x) => s + x.Suma);
            }
        return total;
    }
}
