using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 19
public class Day19 : Day
{
    // Reemplazos 'X => Y', una línea en blanco y la molécula.
    private static (List<(string Origen, string Destino)> Reemplazos, string Molecula) Leer(string[] lines)
    {
        var reemplazos = lines.Where(l => l.Contains(" => ")).Select(l => l.Split(" => ")).Select(p => (p[0], p[1].Trim())).ToList();
        return (reemplazos, lines.Last(l => l.Trim().Length > 0 && !l.Contains(" => ")).Trim());
    }

    private static IEnumerable<int> Apariciones(string texto, string trozo)
    {
        for (int i = texto.IndexOf(trozo, StringComparison.Ordinal); i >= 0; i = texto.IndexOf(trozo, i + 1, StringComparison.Ordinal)) yield return i;
    }

    public override object? Part1(string[] lines)
    {
        var (reemplazos, molecula) = Leer(lines);
        var resultados = new HashSet<string>();
        foreach (var (origen, destino) in reemplazos)
            foreach (int i in Apariciones(molecula, origen)) // cada aparición del origen es un reemplazo posible
                resultados.Add(molecula[..i] + destino + molecula[(i + origen.Length)..]);
        return resultados.Count;
    }

    // Pasos mínimos de 'e' a la molécula: búsqueda en anchura hacia atrás (de la molécula a 'e'). Solo sirve para moléculas cortas.
    private static int PasosBusqueda(List<(string Origen, string Destino)> reemplazos, string molecula)
    {
        var actual = new HashSet<string> { molecula };
        int pasos = 0;
        while (!actual.Contains("e"))
        {
            pasos++;
            var siguiente = new HashSet<string>();
            foreach (var m in actual)
                foreach (var (origen, destino) in reemplazos)
                    foreach (int i in Apariciones(m, destino))
                    {
                        var nueva = m[..i] + origen + m[(i + destino.Length)..];
                        if (origen != "e" || nueva == "e") siguiente.Add(nueva); // 'e' solo vale como paso final
                    }
            actual = siguiente;
        }
        return pasos;
    }

    public override object? Part2(string[] lines)
    {
        var (reemplazos, molecula) = Leer(lines);
        if (!molecula.Contains("Rn")) return PasosBusqueda(reemplazos, molecula);
        // Molécula real: cada reemplazo suma un elemento, salvo los de la forma X => X Rn ... Ar (que añaden Rn y Ar)
        // y los que llevan Y (cada Y añade además una coma y otro elemento). Por eso los pasos son:
        // elementos - (Rn + Ar) - 2 * Y - 1
        int Cuenta(string t) => Apariciones(molecula, t).Count();
        return molecula.Count(char.IsAsciiLetterUpper) - Cuenta("Rn") - Cuenta("Ar") - 2 * Cuenta("Y") - 1;
    }
}
