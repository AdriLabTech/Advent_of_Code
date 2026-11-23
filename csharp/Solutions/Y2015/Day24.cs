using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 24
public class Day24 : Day
{
    // Recorre los subconjuntos de `paquetes` que suman `peso`; se detiene cuando `f` devuelve false.
    private static void Combinaciones(long[] paquetes, long peso, Func<List<long>, bool> f)
    {
        bool Rec(int desde, long resta, List<long> actual)
        {
            if (resta == 0) return f(actual);
            for (int i = desde; i < paquetes.Length; i++)
            {
                if (paquetes[i] > resta) continue;
                actual.Add(paquetes[i]);
                bool seguir = Rec(i + 1, resta - paquetes[i], actual);
                actual.RemoveAt(actual.Count - 1);
                if (!seguir) return false;
            }
            return true;
        }
        Rec(0, peso, new List<long>());
    }

    // ¿Se pueden repartir los paquetes en `grupos` grupos de `peso` cada uno?
    private static bool SePuedeRepartir(long[] paquetes, int grupos, long peso)
    {
        if (grupos == 1) return paquetes.Sum() == peso;
        bool hallado = false;
        Combinaciones(paquetes, peso, grupo =>
        {
            hallado = SePuedeRepartir(paquetes.Where(p => !grupo.Contains(p)).ToArray(), grupos - 1, peso);
            return !hallado; // seguir buscando mientras no se haya hallado
        });
        return hallado;
    }

    private static long? MejorEntrelazamiento(string[] lines, int grupos)
    {
        var paquetes = lines.Where(l => !string.IsNullOrWhiteSpace(l)).Select(long.Parse).ToArray();
        long peso = paquetes.Sum() / grupos;
        // se buscan todos los primeros grupos que suman el peso; interesa el de menos paquetes y, a igualdad, el de menor producto
        (int Tamano, long Producto)? mejor = null;
        Combinaciones(paquetes, peso, grupo =>
        {
            var clave = (grupo.Count, grupo.Aggregate(1L, (a, b) => a * b));
            if (mejor is null || clave.CompareTo(mejor.Value) < 0)
                if (SePuedeRepartir(paquetes.Where(p => !grupo.Contains(p)).ToArray(), grupos - 1, peso)) mejor = clave;
            return true;
        });
        return mejor?.Producto;
    }

    public override object? Part1(string[] lines) => MejorEntrelazamiento(lines, 3);

    public override object? Part2(string[] lines) => MejorEntrelazamiento(lines, 4);
}
