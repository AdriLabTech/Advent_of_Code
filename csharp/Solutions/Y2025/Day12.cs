using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 12
public class Day12 : Day
{
    private static (Dictionary<int, List<(int R, int C)>> Formas, List<(int Ancho, int Alto, int[] Cantidades)> Regiones) Leer(string[] lines)
    {
        var formas = new Dictionary<int, List<(int, int)>>();
        var regiones = new List<(int, int, int[])>();
        foreach (var bloque in Input.Paragraphs(lines))
        {
            if (bloque[0].EndsWith(':'))
                formas[int.Parse(bloque[0][..^1])] = bloque.Skip(1)
                    .SelectMany((fila, r) => fila.Select((ch, c) => (ch, r, c)).Where(t => t.ch == '#').Select(t => (t.r, t.c))).ToList();
            else
                foreach (var linea in bloque)
                {
                    var p = linea.Split(':');
                    var tam = p[0].Split('x');
                    regiones.Add((int.Parse(tam[0]), int.Parse(tam[1]), p[1].Split(' ', StringSplitOptions.RemoveEmptyEntries).Select(int.Parse).ToArray()));
                }
        }
        return (formas, regiones);
    }

    // Las rotaciones y reflejos distintos de una forma, normalizados a la esquina superior izquierda.
    private static List<(int R, int C)[]> Orientaciones(List<(int R, int C)> forma)
    {
        var vistas = new HashSet<string>();
        var resultado = new List<(int R, int C)[]>();
        var celdas = forma;
        for (int giro = 0; giro < 4; giro++)
        {
            celdas = celdas.Select(p => (R: p.C, C: -p.R)).ToList(); // rotar 90°
            foreach (var espejo in new[] { celdas, celdas.Select(p => (R: p.R, C: -p.C)).ToList() })
            {
                int menorR = espejo.Min(p => p.R), menorC = espejo.Min(p => p.C);
                var normal = espejo.Select(p => (R: p.R - menorR, C: p.C - menorC)).Order().ToArray();
                if (vistas.Add(string.Join(";", normal))) resultado.Add(normal);
            }
        }
        return resultado;
    }

    private sealed class Tablero(int ancho, int alto, int[] cantidades, Dictionary<int, List<(int R, int C)[]>> orient)
    {
        private readonly bool[] _libres = Enumerable.Repeat(true, ancho * alto).ToArray();
        private readonly int[] _restantes = (int[])cantidades.Clone();

        // Rellena la primera celda libre (por filas) con una pieza o la deja vacía (si queda holgura).
        public bool Resolver(int pos, int hueco)
        {
            while (pos < ancho * alto && !_libres[pos]) pos++;
            if (pos == ancho * alto) return _restantes.All(q => q == 0);
            int r0 = pos / ancho, c0 = pos % ancho;
            for (int i = 0; i < _restantes.Length; i++)
            {
                if (_restantes[i] == 0) continue;
                foreach (var forma in orient[i])
                {
                    // la primera celda de la forma (por filas) es la que se apoya en la celda libre
                    var (dr, dc) = forma[0];
                    var destino = forma.Select(p => (R: r0 + p.R - dr, C: c0 + p.C - dc)).ToArray();
                    if (!destino.All(p => p.R >= 0 && p.C >= 0 && p.R < alto && p.C < ancho && _libres[p.R * ancho + p.C])) continue;
                    foreach (var p in destino) _libres[p.R * ancho + p.C] = false;
                    _restantes[i]--;
                    if (Resolver(pos + 1, hueco)) return true;
                    _restantes[i]++;
                    foreach (var p in destino) _libres[p.R * ancho + p.C] = true;
                }
            }
            if (hueco > 0)
            {
                _libres[pos] = false; // dejar esta celda vacía
                if (Resolver(pos + 1, hueco - 1)) return true;
                _libres[pos] = true;
            }
            return false;
        }
    }

    public override object? Part1(string[] lines)
    {
        var (formas, regiones) = Leer(lines);
        var orient = formas.ToDictionary(f => f.Key, f => Orientaciones(f.Value));
        int Cabe((int Ancho, int Alto, int[] Cantidades) r)
        {
            int piezas = r.Cantidades.Sum();
            int celdas = r.Cantidades.Select((q, i) => q * formas[i].Count).Sum();
            if (celdas > r.Ancho * r.Alto) return 0; // no caben ni sin huecos
            if (piezas <= r.Ancho / 3 * (r.Alto / 3)) return 1; // cada pieza cabe en un cuadrado de 3x3 y hay sitio para todos
            return new Tablero(r.Ancho, r.Alto, r.Cantidades, orient).Resolver(0, r.Ancho * r.Alto - celdas) ? 1 : 0;
        }
        return regiones.Sum(Cabe);
    }

    public override object? Part2(string[] lines) => null; // pendiente: la parte 2 se desbloquea al completar el resto de días
}
