using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 14
public class Day14 : Day
{
    private const int Carrera = 2503;        // segundos de la carrera
    private const int CarreraEjemplo = 1000; // el ejemplo del enunciado (2 renos) dura 1000 s

    // (velocidad, segundos volando, segundos descansando) de cada reno.
    private static List<(long V, long Vuela, long Descansa)> Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => Input.Ints(l)).Select(n => (n[0], n[1], n[2])).ToList();

    private static long Distancia((long V, long Vuela, long Descansa) r, long segundos)
    {
        long ciclos = segundos / (r.Vuela + r.Descansa), resto = segundos % (r.Vuela + r.Descansa);
        return r.V * (ciclos * r.Vuela + Math.Min(resto, r.Vuela));
    }

    private static int Duracion(List<(long, long, long)> renos) => renos.Count <= 2 ? CarreraEjemplo : Carrera;

    public override object? Part1(string[] lines)
    {
        var renos = Leer(lines);
        return renos.Max(r => Distancia(r, Duracion(renos)));
    }

    // cada segundo, el reno (o renos) que va en cabeza gana un punto
    public override object? Part2(string[] lines)
    {
        var renos = Leer(lines);
        var puntos = new int[renos.Count];
        for (int s = 1; s <= Duracion(renos); s++)
        {
            var d = renos.Select(r => Distancia(r, s)).ToArray();
            for (int i = 0; i < d.Length; i++) if (d[i] == d.Max()) puntos[i]++;
        }
        return puntos.Max();
    }
}
