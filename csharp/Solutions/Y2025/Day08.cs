using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2025;

// Advent of Code 2025 - Día 8
public class Day08 : Day
{
    private const int Conexiones = 1000; // pares más cercanos que se conectan en la parte 1
    private const int ConexionesEjemplo = 10; // el ejemplo del enunciado (20 cajas) conecta solo 10

    private sealed class Circuitos(int n)
    {
        public readonly int[] Padre = Enumerable.Range(0, n).ToArray();
        public readonly int[] Tamano = Enumerable.Repeat(1, n).ToArray();

        public int Raiz(int i)
        {
            while (Padre[i] != i) { Padre[i] = Padre[Padre[i]]; i = Padre[i]; }
            return i;
        }

        // Une los circuitos de i y j. Devuelve false si ya estaban unidos.
        public bool Unir(int i, int j)
        {
            int ri = Raiz(i), rj = Raiz(j);
            if (ri == rj) return false;
            if (Tamano[ri] < Tamano[rj]) (ri, rj) = (rj, ri);
            Padre[rj] = ri;
            Tamano[ri] += Tamano[rj];
            return true;
        }
    }

    private static long[][] Leer(string[] lines) =>
        lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(l => l.Split(',').Select(long.Parse).ToArray()).ToArray();

    // Recorre los pares por distancia creciente (Kruskal) y une los circuitos de cada par.
    // Se detiene tras limitePares pares (cuenten o no como unión) o al quedar un solo circuito.
    // Devuelve (tamaños de los circuitos, último par que unió dos circuitos distintos).
    private static (List<long> Tamanos, (int I, int J) Ultimo) Conectar(long[][] cajas, int? limitePares)
    {
        int n = cajas.Length;
        var pares = new List<(long Dist, int I, int J)>();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                pares.Add((Enumerable.Range(0, 3).Sum(k => (cajas[i][k] - cajas[j][k]) * (cajas[i][k] - cajas[j][k])), i, j));
        pares.Sort();

        var c = new Circuitos(n);
        int circuitos = n;
        (int, int) ultimo = (0, 0);
        for (int visitados = 0; visitados < pares.Count; visitados++)
        {
            if (visitados == limitePares || circuitos == 1) break;
            var (_, i, j) = pares[visitados];
            if (c.Unir(i, j)) // si ya estaban en el mismo circuito no pasa nada
            {
                circuitos--;
                ultimo = (i, j);
            }
        }
        return (Enumerable.Range(0, n).Where(i => c.Padre[i] == i).Select(i => (long)c.Tamano[i]).ToList(), ultimo);
    }

    public override object? Part1(string[] lines)
    {
        var cajas = Leer(lines);
        var (tamanos, _) = Conectar(cajas, cajas.Length <= 20 ? ConexionesEjemplo : Conexiones);
        return tamanos.OrderDescending().Take(3).Aggregate(1L, (a, b) => a * b);
    }

    public override object? Part2(string[] lines)
    {
        var cajas = Leer(lines);
        var (_, (i, j)) = Conectar(cajas, null); // la última unión es la que deja un solo circuito
        return cajas[i][0] * cajas[j][0];
    }
}
