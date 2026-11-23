package utils_2015;

import java.io.IOException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day22 {
    // {coste, daño, curación, duración del efecto}; el orden es Misil, Drenaje, Escudo, Veneno, Recarga
    private static final int[][] HECHIZOS = { { 53, 4, 0, 0 }, { 73, 2, 2, 0 }, { 113, 0, 0, 6 }, { 173, 0, 0, 6 },
            { 229, 0, 0, 5 } };

    public static String solvePart1(int year, int day) throws IOException {
        int[] n = leer(Utils.readInput(year, day));
        return String.valueOf(minimoMana(n[0], n[1], 50, 500, false));
    }

    public static String solvePart2(int year, int day) throws IOException {
        int[] n = leer(Utils.readInput(year, day));
        return String.valueOf(minimoMana(n[0], n[1], 50, 500, true));
    }

    private static int[] leer(List<String> lines) {
        Matcher m = Pattern.compile("\\d+").matcher(String.join(" ", lines));
        int[] n = new int[2];
        for (int i = 0; i < 2 && m.find(); i++) {
            n[i] = Integer.parseInt(m.group());
        }
        return n;
    }

    /** Aplica los efectos al comienzo de un turno sobre {vidaJefe, mana, armadura, escudo, veneno, recarga}. */
    private static int[] efectos(int vidaJefe, int mana, int escudo, int veneno, int recarga) {
        return new int[] { vidaJefe - (veneno > 0 ? 3 : 0), mana + (recarga > 0 ? 101 : 0), escudo > 0 ? 7 : 0,
                Math.max(0, escudo - 1), Math.max(0, veneno - 1), Math.max(0, recarga - 1) };
    }

    /**
     * Búsqueda de Dijkstra por maná gastado sobre los estados del combate: {gastado, vida,
     * maná, vidaJefe, escudo, veneno, recarga}. -1 si no se puede ganar.
     */
    private static int minimoMana(int vidaJefe, int danoJefe, int vida, int mana, boolean dificil) {
        PriorityQueue<int[]> cola = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        cola.add(new int[] { 0, vida, mana, vidaJefe, 0, 0, 0 });
        Set<String> vistos = new HashSet<>();
        while (!cola.isEmpty()) {
            int[] s = cola.poll();
            if (s[3] <= 0) {
                return s[0]; // estado ganador: se saca por maná creciente, es el mínimo
            }
            if (!vistos.add(Arrays.toString(Arrays.copyOfRange(s, 1, 7)))) {
                continue;
            }
            // --- turno del jugador ---
            int vidaJ = s[1];
            if (dificil && --vidaJ <= 0) {
                continue;
            }
            int[] ef = efectos(s[3], s[2], s[4], s[5], s[6]);
            if (ef[0] <= 0) {
                return s[0];
            }
            for (int h = 0; h < HECHIZOS.length; h++) {
                int[] hz = HECHIZOS[h];
                if (hz[0] > ef[1] || (h == 2 && ef[3] > 0) || (h == 3 && ef[4] > 0) || (h == 4 && ef[5] > 0)) {
                    continue;
                }
                int m = ef[1] - hz[0];
                int vj = ef[0] - hz[1];
                int v = vidaJ + hz[2];
                int e = h == 2 ? hz[3] : ef[3];
                int p = h == 3 ? hz[3] : ef[4];
                int r = h == 4 ? hz[3] : ef[5];
                int gastado = s[0] + hz[0];
                if (vj <= 0) { // gana nada más lanzarlo
                    cola.add(new int[] { gastado, v, m, vj, e, p, r });
                    continue;
                }
                // --- turno del jefe ---
                int[] ef2 = efectos(vj, m, e, p, r);
                if (ef2[0] <= 0) {
                    cola.add(new int[] { gastado, v, ef2[1], ef2[0], ef2[3], ef2[4], ef2[5] });
                    continue;
                }
                v -= Math.max(1, danoJefe - ef2[2]);
                if (v > 0) {
                    cola.add(new int[] { gastado, v, ef2[1], ef2[0], ef2[3], ef2[4], ef2[5] });
                }
            }
        }
        return -1;
    }
}
