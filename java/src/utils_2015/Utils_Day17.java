package utils_2015;

import java.io.IOException;
import java.util.List;
import utils.Utils;

public class Utils_Day17 {
    private static final int LITROS = 150;
    private static final int LITROS_EJEMPLO = 25; // el ejemplo del enunciado (5 contenedores) guarda 25 litros

    public static String solvePart1(int year, int day) throws IOException {
        long total = 0;
        for (long f : formasPorCantidad(Utils.readInput(year, day))) {
            total += f;
        }
        return String.valueOf(total);
    }

    public static String solvePart2(int year, int day) throws IOException {
        // formas con el menor número posible de contenedores
        for (long f : formasPorCantidad(Utils.readInput(year, day))) {
            if (f > 0) {
                return String.valueOf(f);
            }
        }
        return "-";
    }

    /** formas[n] = de cuántas maneras se llenan exactamente los litros con n contenedores (programación dinámica). */
    private static long[] formasPorCantidad(List<String> lines) {
        int[] contenedores = lines.stream().filter(l -> !l.isBlank()).mapToInt(l -> Integer.parseInt(l.trim())).toArray();
        int litros = contenedores.length <= 5 ? LITROS_EJEMPLO : LITROS;
        long[][] tabla = new long[contenedores.length + 1][litros + 1]; // tabla[n][s]: n contenedores que suman s litros
        tabla[0][0] = 1;
        for (int c : contenedores) {
            for (int n = contenedores.length - 1; n >= 0; n--) {
                for (int s = litros - c; s >= 0; s--) {
                    tabla[n + 1][s + c] += tabla[n][s];
                }
            }
        }
        long[] formas = new long[contenedores.length + 1];
        for (int n = 0; n < formas.length; n++) {
            formas[n] = tabla[n][litros];
        }
        return formas;
    }
}
