package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day21 {
    // {coste, daño, armadura} de la tienda
    private static final int[][] ARMAS = { { 8, 4, 0 }, { 10, 5, 0 }, { 25, 6, 0 }, { 40, 7, 0 }, { 74, 8, 0 } };
    private static final int[][] ARMADURAS = { { 0, 0, 0 }, { 13, 0, 1 }, { 31, 0, 2 }, { 53, 0, 3 }, { 75, 0, 4 },
            { 102, 0, 5 } }; // la primera = sin armadura
    private static final int[][] ANILLOS = { { 25, 1, 0 }, { 50, 2, 0 }, { 100, 3, 0 }, { 20, 0, 1 }, { 40, 0, 2 },
            { 80, 0, 3 } };

    public static String solvePart1(int year, int day) throws IOException {
        long[] jefe = leerJefe(Utils.readInput(year, day));
        int mejor = Integer.MAX_VALUE;
        for (int[] e : equipamientos()) {
            if (ganaJugador(100, e[1], e[2], jefe)) {
                mejor = Math.min(mejor, e[0]);
            }
        }
        return String.valueOf(mejor);
    }

    public static String solvePart2(int year, int day) throws IOException {
        long[] jefe = leerJefe(Utils.readInput(year, day));
        int mejor = 0;
        for (int[] e : equipamientos()) {
            if (!ganaJugador(100, e[1], e[2], jefe)) {
                mejor = Math.max(mejor, e[0]);
            }
        }
        return String.valueOf(mejor);
    }

    private static long[] leerJefe(List<String> lines) {
        Matcher m = Pattern.compile("\\d+").matcher(String.join(" ", lines));
        long[] n = new long[3];
        for (int i = 0; i < 3 && m.find(); i++) {
            n[i] = Long.parseLong(m.group());
        }
        return n;
    }

    /** Gana quien tarda menos turnos en matar al otro (el jugador pega primero, así que gana en un empate). */
    private static boolean ganaJugador(int vida, int dano, int armadura, long[] jefe) {
        long da = Math.max(1, dano - jefe[2]);
        long db = Math.max(1, jefe[1] - armadura);
        return (jefe[0] + da - 1) / da <= (vida + db - 1) / db;
    }

    /** {coste, daño, armadura} de cada compra posible: 1 arma, 0-1 armadura y 0-2 anillos. */
    private static List<int[]> equipamientos() {
        List<List<int[]>> anillos = new ArrayList<>();
        anillos.add(List.of());
        for (int i = 0; i < ANILLOS.length; i++) {
            anillos.add(List.of(ANILLOS[i]));
            for (int j = i + 1; j < ANILLOS.length; j++) {
                anillos.add(List.of(ANILLOS[i], ANILLOS[j]));
            }
        }
        List<int[]> compras = new ArrayList<>();
        for (int[] arma : ARMAS) {
            for (int[] armadura : ARMADURAS) {
                for (List<int[]> par : anillos) {
                    int[] total = { arma[0] + armadura[0], arma[1] + armadura[1], arma[2] + armadura[2] };
                    for (int[] a : par) {
                        for (int k = 0; k < 3; k++) {
                            total[k] += a[k];
                        }
                    }
                    compras.add(total);
                }
            }
        }
        return compras;
    }
}
