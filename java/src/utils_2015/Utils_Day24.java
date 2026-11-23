package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;
import utils.Utils;

public class Utils_Day24 {

    public static String solvePart1(int year, int day) throws IOException {
        return mejorEntrelazamiento(Utils.readInput(year, day), 3);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return mejorEntrelazamiento(Utils.readInput(year, day), 4);
    }

    private static String mejorEntrelazamiento(List<String> lines, int grupos) {
        long[] paquetes = lines.stream().filter(l -> !l.isBlank()).mapToLong(l -> Long.parseLong(l.trim())).toArray();
        long peso = java.util.Arrays.stream(paquetes).sum() / grupos;
        // se buscan todos los primeros grupos que suman el peso; interesa el de menos paquetes y,
        // a igualdad, el de menor producto
        long[] mejor = { -1, -1 }; // {tamaño, producto}
        combinaciones(paquetes, peso, grupo -> {
            long producto = grupo.stream().reduce(1L, (x, y) -> x * y);
            boolean mejora = mejor[0] < 0 || grupo.size() < mejor[0] || (grupo.size() == mejor[0] && producto < mejor[1]);
            if (mejora && sePuedeRepartir(sin(paquetes, grupo), grupos - 1, peso)) {
                mejor[0] = grupo.size();
                mejor[1] = producto;
            }
            return true;
        });
        return mejor[0] < 0 ? "-" : String.valueOf(mejor[1]);
    }

    /** Recorre los subconjuntos de paquetes que suman peso; se detiene cuando f devuelve false. */
    private static void combinaciones(long[] paquetes, long peso, Predicate<List<Long>> f) {
        rec(paquetes, 0, peso, new ArrayList<>(), f);
    }

    private static boolean rec(long[] paquetes, int desde, long resta, List<Long> actual, Predicate<List<Long>> f) {
        if (resta == 0) {
            return f.test(actual);
        }
        for (int i = desde; i < paquetes.length; i++) {
            if (paquetes[i] > resta) {
                continue;
            }
            actual.add(paquetes[i]);
            boolean seguir = rec(paquetes, i + 1, resta - paquetes[i], actual, f);
            actual.remove(actual.size() - 1);
            if (!seguir) {
                return false;
            }
        }
        return true;
    }

    private static long[] sin(long[] paquetes, List<Long> grupo) {
        return java.util.Arrays.stream(paquetes).filter(p -> !grupo.contains(p)).toArray();
    }

    /** ¿Se pueden repartir los paquetes en {@code grupos} grupos de {@code peso} cada uno? */
    private static boolean sePuedeRepartir(long[] paquetes, int grupos, long peso) {
        if (grupos == 1) {
            return java.util.Arrays.stream(paquetes).sum() == peso;
        }
        boolean[] hallado = { false };
        combinaciones(paquetes, peso, grupo -> {
            hallado[0] = sePuedeRepartir(sin(paquetes, grupo), grupos - 1, peso);
            return !hallado[0]; // seguir buscando mientras no se haya hallado
        });
        return hallado[0];
    }
}
