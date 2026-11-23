using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 9
public class Day09 : Day
{
    private static List<(long X, long Y)> Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => l.Split(',')).Select(p => (long.Parse(p[0]), long.Parse(p[1]))).ToList();

    private static long Area((long X, long Y) a, (long X, long Y) b) => (Math.Abs(a.X - b.X) + 1) * (Math.Abs(a.Y - b.Y) + 1);

    public override object? Part1(string[] lines)
    {
        var puntos = Leer(lines).Distinct().ToList();
        long mejor = 0;
        for (int i = 0; i < puntos.Count; i++)
            for (int j = i + 1; j < puntos.Count; j++)
                mejor = Math.Max(mejor, Area(puntos[i], puntos[j]));
        return mejor;
    }

    public override object? Part2(string[] lines)
    {
        var rojas = Leer(lines);

        // 1) Compresión de coordenadas: solo importan los valores usados (y sus vecinos, para tener borde exterior)
        var xs = rojas.SelectMany(p => new[] { p.X - 1, p.X, p.X + 1 }).Distinct().Order().ToList();
        var ys = rojas.SelectMany(p => new[] { p.Y - 1, p.Y, p.Y + 1 }).Distinct().Order().ToList();
        var ix = xs.Select((x, i) => (x, i)).ToDictionary(t => t.x, t => t.i);
        var iy = ys.Select((y, i) => (y, i)).ToDictionary(t => t.y, t => t.i);
        int alto = ys.Count, ancho = xs.Count;

        // 2) Borde del polígono (los lados unen cada punto con el siguiente)
        var borde = new bool[alto, ancho];
        for (int k = 0; k < rojas.Count; k++)
        {
            var (a, b) = (rojas[k], rojas[(k + 1) % rojas.Count]);
            for (int y = Math.Min(iy[a.Y], iy[b.Y]); y <= Math.Max(iy[a.Y], iy[b.Y]); y++)
                for (int x = Math.Min(ix[a.X], ix[b.X]); x <= Math.Max(ix[a.X], ix[b.X]); x++)
                    borde[y, x] = true;
        }

        // 3) Relleno desde fuera: lo que no se alcanza está dentro del polígono
        var exterior = new bool[alto, ancho];
        var cola = new Queue<(int Y, int X)>();
        for (int y = 0; y < alto; y++)
            for (int x = 0; x < ancho; x++)
                if ((y == 0 || y == alto - 1 || x == 0 || x == ancho - 1) && !borde[y, x])
                {
                    exterior[y, x] = true;
                    cola.Enqueue((y, x));
                }
        (int, int)[] direcciones = { (-1, 0), (1, 0), (0, -1), (0, 1) };
        while (cola.Count > 0)
        {
            var (y, x) = cola.Dequeue();
            foreach (var (dy, dx) in direcciones)
            {
                int ny = y + dy, nx = x + dx;
                if (ny >= 0 && ny < alto && nx >= 0 && nx < ancho && !borde[ny, nx] && !exterior[ny, nx])
                {
                    exterior[ny, nx] = true;
                    cola.Enqueue((ny, nx));
                }
            }
        }

        // 4) Sumas acumuladas 2D de las celdas permitidas (borde o interior)
        var suma = new int[alto + 1, ancho + 1];
        for (int y = 0; y < alto; y++)
            for (int x = 0; x < ancho; x++)
                suma[y + 1, x + 1] = suma[y, x + 1] + suma[y + 1, x] - suma[y, x] + (borde[y, x] || !exterior[y, x] ? 1 : 0);

        // 5) Mayor rectángulo cuyas celdas están todas permitidas
        long mejor = 0;
        for (int i = 0; i < rojas.Count; i++)
            for (int j = i + 1; j < rojas.Count; j++)
            {
                var (p1, p2) = (rojas[i], rojas[j]);
                long area = Area(p1, p2);
                if (area <= mejor) continue;
                int x1 = Math.Min(ix[p1.X], ix[p2.X]), x2 = Math.Max(ix[p1.X], ix[p2.X]);
                int y1 = Math.Min(iy[p1.Y], iy[p2.Y]), y2 = Math.Max(iy[p1.Y], iy[p2.Y]);
                int dentro = suma[y2 + 1, x2 + 1] - suma[y1, x2 + 1] - suma[y2 + 1, x1] + suma[y1, x1];
                if (dentro == (x2 - x1 + 1) * (y2 - y1 + 1)) mejor = area;
            }
        return mejor;
    }
}
