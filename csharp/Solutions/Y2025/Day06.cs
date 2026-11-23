using System.Numerics;
using System.Text.RegularExpressions;
using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 6
public class Day06 : Day
{
    public override object? Part1(string[] lines)
    {
        // cada columna de la hoja: varios números y, al final, el operador
        var columnas = new SortedDictionary<int, List<string>>();
        foreach (var line in lines.Where(l => !string.IsNullOrWhiteSpace(l)))
        {
            var tokens = Regex.Matches(line, line.Contains('*') ? @"[*+]" : @"\d+").Select(m => m.Value);
            int i = 0;
            foreach (var t in tokens)
            {
                if (!columnas.TryGetValue(i, out var col)) columnas[i] = col = new List<string>();
                col.Add(t);
                i++;
            }
        }

        BigInteger total = 0;
        foreach (var col in columnas.Values)
        {
            var valores = col.Take(col.Count - 1).Select(BigInteger.Parse).ToList();
            total += col[^1] switch
            {
                "+" => valores.Aggregate((a, b) => a + b),
                "*" => valores.Aggregate((a, b) => a * b),
                _ => valores[0],
            };
        }
        return total;
    }

    public override object? Part2(string[] lines)
    {
        // se lee carácter a carácter: cada columna de la hoja es un número y el operador marca el grupo
        var filas = lines.Where(l => !string.IsNullOrWhiteSpace(l)).ToArray();
        BigInteger total = 0;
        BigInteger? acumulado = null;
        bool enGrupo = false, multiplica = false;
        for (int i = 0; i < filas.Max(f => f.Length); i++)
        {
            var columna = filas.Where(f => i < f.Length).Select(f => f[i]).ToArray();
            if (columna[^1] is '+' or '*') // empieza un grupo nuevo
            {
                (multiplica, enGrupo, acumulado) = (columna[^1] == '*', true, null);
            }
            var texto = new string(columna[..^1]).Trim();
            if (texto.Length == 0) // columna vacía = fin del grupo
            {
                if (enGrupo) total += acumulado ?? 0;
                enGrupo = false;
                continue;
            }
            var valor = BigInteger.Parse(texto);
            acumulado = acumulado is null ? valor : multiplica ? acumulado * valor : acumulado + valor;
        }
        if (enGrupo) total += acumulado ?? 0; // el último grupo no tiene columna vacía detrás
        return total;
    }
}
