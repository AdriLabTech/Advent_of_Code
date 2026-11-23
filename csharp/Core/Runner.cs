using System.Diagnostics;
using System.Text.RegularExpressions;

namespace AdventOfCode.Core;

public static class Runner
{
    private const string Bar = "============================================================";

    // Descubre todas las clases Day{NN} en namespaces ...Solutions.Y{año}
    private static List<(int Year, int Day, Type Type)> Discover() =>
        typeof(Day).Assembly.GetTypes()
            .Where(t => !t.IsAbstract && typeof(Day).IsAssignableFrom(t))
            .Select(t => (m: Regex.Match($"{t.Namespace}.{t.Name}", @"\.Y(\d{4})\.Day(\d{2})$"), t))
            .Where(x => x.m.Success)
            .Select(x => (int.Parse(x.m.Groups[1].Value), int.Parse(x.m.Groups[2].Value), x.t))
            .OrderBy(x => x.Item1).ThenBy(x => x.Item2)
            .ToList();

    public static int Main(string[] args)
    {
        var example = args.Contains("--example");
        var nums = args.Where(a => int.TryParse(a, out _)).Select(int.Parse).ToArray();
        if (nums.Length == 0)
        {
            Console.Error.WriteLine("Uso: dotnet run -c Release -- <año> [día] [--example]");
            return 2;
        }
        var year = nums[0];
        var days = Discover().Where(d => d.Year == year && (nums.Length < 2 || d.Day == nums[1])).ToList();
        if (days.Count == 0)
        {
            Console.WriteLine("No hay días implementados para ese año/día (crea uno con scripts/new_day.py)");
            return 1;
        }
        var done = days.Count(d => RunDay(d.Year, d.Day, d.Type, example));
        if (nums.Length == 1)
            Console.WriteLine($"\n{Bar}\nADVENT OF CODE {year}: {done}/{days.Count} días ejecutados\n{Bar}");
        return done == 0 ? 1 : 0;
    }

    private static bool RunDay(int year, int dayNumber, Type type, bool example)
    {
        var path = Input.PathFor(year, dayNumber, example);
        if (!File.Exists(path)) { Console.WriteLine($"No encuentro el input: {path}"); return false; }

        var lines = Input.ReadLines(year, dayNumber, example);
        var day = (Day)Activator.CreateInstance(type)!;
        Console.WriteLine($"\n{Bar}\n🎄 Advent of Code {year} - Día {dayNumber:00}{(example ? " (ejemplo)" : "")} 🎄\n{Bar}");
        var sw = Stopwatch.StartNew();
        var r1 = day.Part1(lines);
        var r2 = day.Part2(lines);
        sw.Stop();
        Console.WriteLine($"Parte 1: {r1 ?? "-"}");
        Console.WriteLine($"Parte 2: {r2 ?? "-"}");
        Console.WriteLine($"Tiempo: {sw.Elapsed.TotalMilliseconds:F1} ms");
        return true;
    }
}
