package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day14 {
    private static final int CARRERA = 2503; // segundos de la carrera
    private static final int CARRERA_EJEMPLO = 1000; // el ejemplo del enunciado (2 renos) dura 1000 s

    public static String solvePart1(int year, int day) throws IOException {
        List<int[]> renos = leer(Utils.readInput(year, day));
        long mejor = 0;
        for (int[] r : renos) {
            mejor = Math.max(mejor, distancia(r, duracion(renos)));
        }
        return String.valueOf(mejor);
    }

    public static String solvePart2(int year, int day) throws IOException {
        // cada segundo, el reno (o renos) que va en cabeza gana un punto
        List<int[]> renos = leer(Utils.readInput(year, day));
        int[] puntos = new int[renos.size()];
        for (int s = 1; s <= duracion(renos); s++) {
            long maxima = 0;
            for (int[] r : renos) {
                maxima = Math.max(maxima, distancia(r, s));
            }
            for (int i = 0; i < puntos.length; i++) {
                if (distancia(renos.get(i), s) == maxima) {
                    puntos[i]++;
                }
            }
        }
        int mejor = 0;
        for (int p : puntos) {
            mejor = Math.max(mejor, p);
        }
        return String.valueOf(mejor);
    }

    /** {velocidad, segundos volando, segundos descansando} de cada reno. */
    private static List<int[]> leer(List<String> lines) {
        List<int[]> renos = new ArrayList<>();
        for (String line : lines) {
            Matcher m = Pattern.compile("\\d+").matcher(line);
            int[] n = new int[3];
            for (int i = 0; i < 3 && m.find(); i++) {
                n[i] = Integer.parseInt(m.group());
            }
            if (!line.isBlank()) {
                renos.add(n);
            }
        }
        return renos;
    }

    private static long distancia(int[] r, int segundos) {
        long ciclos = segundos / (r[1] + r[2]);
        long resto = segundos % (r[1] + r[2]);
        return (long) r[0] * (ciclos * r[1] + Math.min(resto, r[1]));
    }

    private static int duracion(List<int[]> renos) {
        return renos.size() <= 2 ? CARRERA_EJEMPLO : CARRERA;
    }
}
