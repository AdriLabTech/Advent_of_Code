package utils_2015;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import utils.Utils;

public class Utils_Day09 {
    private static int minimo;
    private static int maximo;

    public static String solvePart1(int year, int day) throws IOException {
        return String.valueOf(rutas(Utils.readInput(year, day))[0]);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(rutas(Utils.readInput(year, day))[1]);
    }

    /**
     * {ruta más corta, ruta más larga} que visitan todas las ciudades exactamente
     * una vez (hay pocas: se prueban todas).
     */
    private static int[] rutas(List<String> lines) {
        Map<String, Integer> ids = new HashMap<>();
        int[][] tramos = new int[lines.size()][];
        int t = 0;
        for (String line : lines) {
            if (line.isBlank()) {
                continue;
            }
            String[] p = line.split(" = ");
            String[] ciudades = p[0].split(" to ");
            ids.putIfAbsent(ciudades[0], ids.size());
            ids.putIfAbsent(ciudades[1], ids.size());
            tramos[t++] = new int[] { ids.get(ciudades[0]), ids.get(ciudades[1]), Integer.parseInt(p[1].trim()) };
        }
        int n = ids.size();
        int[][] d = new int[n][n];
        for (int i = 0; i < t; i++) {
            d[tramos[i][0]][tramos[i][1]] = tramos[i][2];
            d[tramos[i][1]][tramos[i][0]] = tramos[i][2];
        }
        minimo = Integer.MAX_VALUE;
        maximo = 0;
        for (int inicio = 0; inicio < n; inicio++) {
            recorrer(inicio, 1 << inicio, 0, d);
        }
        return new int[] { minimo, maximo };
    }

    private static void recorrer(int actual, int visitadas, int recorrido, int[][] d) {
        if (Integer.bitCount(visitadas) == d.length) {
            minimo = Math.min(minimo, recorrido);
            maximo = Math.max(maximo, recorrido);
            return;
        }
        for (int s = 0; s < d.length; s++) {
            if ((visitadas >> s & 1) == 0) {
                recorrer(s, visitadas | 1 << s, recorrido + d[actual][s], d);
            }
        }
    }
}
