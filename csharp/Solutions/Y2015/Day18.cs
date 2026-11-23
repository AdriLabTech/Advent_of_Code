using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 18
public class Day18 : Day
{
    private const int Pasos = 100;
    private static readonly (int Parte1, int Parte2) PasosEjemplo = (4, 5); // el ejemplo (6x6) usa 4 pasos en la parte 1 y 5 en la parte 2

    // Una generación del juego de la vida (los vecinos fuera de la rejilla cuentan como apagados).
    private static bool[,] Paso(bool[,] luces)
    {
        int lado = luces.GetLength(0);
        var nuevas = new bool[lado, lado];
        for (int r = 0; r < lado; r++)
            for (int c = 0; c < lado; c++)
            {
                int vecinos = 0;
                for (int dr = -1; dr <= 1; dr++)
                    for (int dc = -1; dc <= 1; dc++)
                        if ((dr != 0 || dc != 0) && r + dr >= 0 && r + dr < lado && c + dc >= 0 && c + dc < lado && luces[r + dr, c + dc]) vecinos++;
                nuevas[r, c] = vecinos == 3 || (vecinos == 2 && luces[r, c]);
            }
        return nuevas;
    }

    private static int Animar(string[] lines, bool esquinasFijas)
    {
        var filas = lines.Select(l => l.Trim()).Where(l => l.Length > 0).ToArray();
        int lado = filas.Length;
        var luces = new bool[lado, lado];
        for (int r = 0; r < lado; r++) for (int c = 0; c < lado; c++) luces[r, c] = filas[r][c] == '#';
        (int Parte1, int Parte2) pasos = lado <= 6 ? PasosEjemplo : (Pasos, Pasos);

        void Fijar()
        {
            if (!esquinasFijas) return;
            luces[0, 0] = luces[0, lado - 1] = luces[lado - 1, 0] = luces[lado - 1, lado - 1] = true; // esquinas atascadas encendidas
        }
        Fijar();
        for (int i = 0; i < (esquinasFijas ? pasos.Parte2 : pasos.Parte1); i++) { luces = Paso(luces); Fijar(); }
        return luces.Cast<bool>().Count(l => l);
    }

    public override object? Part1(string[] lines) => Animar(lines, false);

    public override object? Part2(string[] lines) => Animar(lines, true);
}
