using AdventOfCode.Core;

namespace AdventOfCode.Solutions.Y2015;

// Advent of Code 2015 - Día 22
public class Day22 : Day
{
    // (coste, daño, curación, duración del efecto); el orden es Misil, Drenaje, Escudo, Veneno, Recarga
    private static readonly (int Coste, int Dano, int Cura, int Duracion)[] Hechizos = { (53, 4, 0, 0), (73, 2, 2, 0), (113, 0, 0, 6), (173, 0, 0, 6), (229, 0, 0, 5) };

    // Estado del combate: (maná gastado, vida jugador, maná, vida jefe, escudo, veneno, recarga)
    private readonly record struct Estado(int Gastado, int Vida, int Mana, int VidaJefe, int Escudo, int Veneno, int Recarga);

    // Aplica los efectos activos al comienzo de un turno.
    private static (int VidaJefe, int Mana, int Armadura, int Escudo, int Veneno, int Recarga) Efectos(int vidaJefe, int mana, int escudo, int veneno, int recarga) =>
        (vidaJefe - (veneno > 0 ? 3 : 0), mana + (recarga > 0 ? 101 : 0), escudo > 0 ? 7 : 0, Math.Max(0, escudo - 1), Math.Max(0, veneno - 1), Math.Max(0, recarga - 1));

    // Búsqueda de Dijkstra por maná gastado sobre los estados del combate. null si no se puede ganar.
    private static int? MinimoMana(int vidaJefe, int danoJefe, int vida, int mana, bool dificil)
    {
        var cola = new PriorityQueue<Estado, int>();
        cola.Enqueue(new Estado(0, vida, mana, vidaJefe, 0, 0, 0), 0);
        var vistos = new HashSet<(int, int, int, int, int, int)>();
        while (cola.TryDequeue(out var s, out _))
        {
            if (s.VidaJefe <= 0) return s.Gastado; // estado ganador: se saca por maná creciente, es el mínimo
            if (!vistos.Add((s.Vida, s.Mana, s.VidaJefe, s.Escudo, s.Veneno, s.Recarga))) continue;
            // --- turno del jugador ---
            int vidaJ = s.Vida;
            if (dificil && --vidaJ <= 0) continue;
            var (vj0, m0, _, e0, p0, r0) = Efectos(s.VidaJefe, s.Mana, s.Escudo, s.Veneno, s.Recarga);
            if (vj0 <= 0) return s.Gastado;
            for (int h = 0; h < Hechizos.Length; h++)
            {
                var (coste, dano, cura, duracion) = Hechizos[h];
                if (coste > m0 || (h == 2 && e0 > 0) || (h == 3 && p0 > 0) || (h == 4 && r0 > 0)) continue;
                int m = m0 - coste, vj = vj0 - dano, v = vidaJ + cura, e = e0, p = p0, r = r0;
                if (h == 2) e = duracion; else if (h == 3) p = duracion; else if (h == 4) r = duracion;
                int gastado = s.Gastado + coste;
                if (vj <= 0) { cola.Enqueue(new Estado(gastado, v, m, vj, e, p, r), gastado); continue; } // gana nada más lanzarlo
                // --- turno del jefe ---
                int armadura;
                (vj, m, armadura, e, p, r) = Efectos(vj, m, e, p, r);
                if (vj <= 0) { cola.Enqueue(new Estado(gastado, v, m, vj, e, p, r), gastado); continue; }
                v -= Math.Max(1, danoJefe - armadura);
                if (v > 0) cola.Enqueue(new Estado(gastado, v, m, vj, e, p, r), gastado);
            }
        }
        return null;
    }

    public override object? Part1(string[] lines)
    {
        var n = Input.Ints(string.Join(" ", lines));
        return MinimoMana((int)n[0], (int)n[1], 50, 500, false);
    }

    public override object? Part2(string[] lines)
    {
        var n = Input.Ints(string.Join(" ", lines));
        return MinimoMana((int)n[0], (int)n[1], 50, 500, true);
    }
}
