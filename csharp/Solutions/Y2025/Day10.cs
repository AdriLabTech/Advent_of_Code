using System.Text.RegularExpressions;
using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 10
public class Day10 : Day
{
    // '[.##.] (3) (1,3) ... {3,5,4}' -> luces objetivo, botones y contadores objetivo.
    private static (bool[] Luces, int[][] Botones, int[] Contadores) Leer(string line)
    {
        var luces = Regex.Match(line, @"\[(.*?)\]").Groups[1].Value.Select(c => c == '#').ToArray();
        var botones = Regex.Matches(line, @"\(([^)]*)\)")
            .Select(m => m.Groups[1].Value.Split(',', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries).Select(int.Parse).ToArray())
            .ToArray();
        var contadores = Regex.Match(line, @"\{(.*?)\}").Groups[1].Value.Split(',').Select(int.Parse).ToArray();
        return (luces, botones, contadores);
    }

    // Clave de un vector de contadores para usarlo en diccionarios.
    private static string Clave(int[] v) => string.Join(",", v);

    // Para cada combinación de botones (cada uno 0 o 1 veces): incremento de cada contador -> mínimo de pulsaciones.
    private static Dictionary<string, (int[] Incremento, int Pulsaciones)> Patrones(int[][] botones, int n)
    {
        var mejor = new Dictionary<string, (int[], int)>();
        for (int seleccion = 0; seleccion < 1 << botones.Length; seleccion++)
        {
            var incremento = new int[n];
            for (int j = 0; j < botones.Length; j++)
                if ((seleccion >> j & 1) == 1)
                    foreach (var i in botones[j]) incremento[i]++;
            int pulsaciones = int.PopCount(seleccion);
            var clave = Clave(incremento);
            if (!mejor.TryGetValue(clave, out var actual) || pulsaciones < actual.Item2) mejor[clave] = (incremento, pulsaciones);
        }
        return mejor;
    }

    // Truco de la mitad: tras elegir una combinación con la misma paridad, el resto se pulsa por pares.
    private static long Minimo(int[] actual, Dictionary<string, (int[] Incremento, int Pulsaciones)> pats, Dictionary<string, long> memo)
    {
        if (actual.All(v => v == 0)) return 0;
        var clave = Clave(actual);
        if (memo.TryGetValue(clave, out var guardado)) return guardado;

        long mejor = long.MaxValue;
        foreach (var (inc, pulsaciones) in pats.Values)
        {
            bool valido = true;
            for (int i = 0; i < actual.Length && valido; i++) valido = inc[i] <= actual[i] && (actual[i] - inc[i]) % 2 == 0;
            if (!valido) continue;
            var mitad = actual.Select((c, i) => (c - inc[i]) / 2).ToArray();
            long sub = Minimo(mitad, pats, memo);
            if (sub != long.MaxValue) mejor = Math.Min(mejor, pulsaciones + 2 * sub);
        }
        return memo[clave] = mejor;
    }

    public override object? Part1(string[] lines)
    {
        long total = 0;
        foreach (var line in lines.Where(l => !string.IsNullOrWhiteSpace(l)))
        {
            var (luces, botones, _) = Leer(line);
            // solo importa la paridad de cada luz: se busca la combinación con esa paridad y menos pulsaciones
            total += Patrones(botones, luces.Length).Values
                .Where(p => p.Incremento.Select((v, i) => v % 2 == 1 == luces[i]).All(ok => ok))
                .Min(p => p.Pulsaciones);
        }
        return total;
    }

    public override object? Part2(string[] lines)
    {
        long total = 0;
        foreach (var line in lines.Where(l => !string.IsNullOrWhiteSpace(l)))
        {
            var (_, botones, contadores) = Leer(line);
            total += Minimo(contadores, Patrones(botones, contadores.Length), new Dictionary<string, long>());
        }
        return total;
    }
}
