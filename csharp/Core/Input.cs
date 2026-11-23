using System.Text.RegularExpressions;

namespace AdventOfCode.Core;

/// <summary>Lectura de inputs y helpers de parsing.</summary>
public static partial class Input
{
    // csharp/bin/<Config>/<tfm>/aoc.dll -> la raíz del repo se localiza buscando la carpeta "inputs".
    public static string InputsDir()
    {
        var env = Environment.GetEnvironmentVariable("AOC_INPUTS_DIR");
        if (!string.IsNullOrEmpty(env)) return env;
        for (var dir = new DirectoryInfo(AppContext.BaseDirectory); dir != null; dir = dir.Parent)
            if (File.Exists(Path.Combine(dir.FullName, "AdventOfCode.csproj")))
                return Path.GetFullPath(Path.Combine(dir.FullName, "..", "inputs"));
        return Path.GetFullPath(Path.Combine("..", "inputs"));
    }

    public static string PathFor(int year, int day, bool example = false) =>
        Path.Combine(InputsDir(), year.ToString(), $"day{day:00}{(example ? ".example" : "")}.txt");

    public static string[] ReadLines(int year, int day, bool example = false) =>
        File.ReadAllLines(PathFor(year, day, example));

    /// <summary>Todos los enteros (con signo) que aparecen en un texto.</summary>
    public static long[] Ints(string text) =>
        IntRegex().Matches(text).Select(m => long.Parse(m.Value)).ToArray();

    /// <summary>Divide las líneas en bloques separados por líneas en blanco.</summary>
    public static List<string[]> Paragraphs(string[] lines)
    {
        var blocks = new List<string[]>();
        var cur = new List<string>();
        foreach (var l in lines)
        {
            if (string.IsNullOrWhiteSpace(l))
            {
                if (cur.Count > 0) { blocks.Add(cur.ToArray()); cur.Clear(); }
            }
            else cur.Add(l);
        }
        if (cur.Count > 0) blocks.Add(cur.ToArray());
        return blocks;
    }

    [GeneratedRegex(@"-?\d+")]
    private static partial Regex IntRegex();
}
