using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 12
public class Day12 : Day
{
    // Suma de todos los números ignorando los objetos {...} que tengan algún valor "red" (los arrays no cuentan como objeto).
    // Se recorre el texto con una pila: cada { o [ abre un nivel con su suma; al cerrarlo se suma al nivel de fuera
    // (salvo un objeto con "red", que aporta 0).
    private static long SumaSinRojos(string t)
    {
        var pila = new Stack<(long Suma, bool EsObjeto, bool TieneRojo)>();
        pila.Push((0, false, false));
        for (int i = 0; i < t.Length; i++)
        {
            char c = t[i];
            if (c is '{' or '[') pila.Push((0, c == '{', false));
            else if (c is '}' or ']')
            {
                var n = pila.Pop();
                var padre = pila.Pop();
                pila.Push((padre.Suma + (n.TieneRojo ? 0 : n.Suma), padre.EsObjeto, padre.TieneRojo));
            }
            else if (c == '"')
            {
                int fin = t.IndexOf('"', i + 1);
                bool esClave = fin + 1 < t.Length && t[fin + 1] == ':'; // un ':' detrás significa que era una clave, no un valor
                if (t[(i + 1)..fin] == "red" && pila.Peek().EsObjeto && !esClave)
                {
                    var n = pila.Pop();
                    pila.Push((n.Suma, n.EsObjeto, true));
                }
                i = fin;
            }
            else if (c == '-' || char.IsAsciiDigit(c))
            {
                int fin = i + 1;
                while (fin < t.Length && char.IsAsciiDigit(t[fin])) fin++;
                var n = pila.Pop();
                pila.Push((n.Suma + long.Parse(t[i..fin]), n.EsObjeto, n.TieneRojo));
                i = fin - 1;
            }
        }
        return pila.Pop().Suma;
    }

    public override object? Part1(string[] lines) => Input.Ints(lines[0]).Sum();

    public override object? Part2(string[] lines) => SumaSinRojos(lines[0]);
}
