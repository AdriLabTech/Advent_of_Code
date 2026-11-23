package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day15 {
    private static final int CUCHARADAS = 100;
    private static long mejor;

    public static String solvePart1(int year, int day) throws IOException {
        return String.valueOf(mejorGalleta(Utils.readInput(year, day), null));
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(mejorGalleta(Utils.readInput(year, day), 500L));
    }

    /** Prueba todos los repartos de las cucharadas entre los ingredientes y devuelve la mejor puntuación. */
    private static long mejorGalleta(List<String> lines, Long calorias) {
        // capacidad, durabilidad, sabor, textura, calorías
        List<long[]> ing = new ArrayList<>();
        for (String line : lines) {
            if (line.isBlank()) {
                continue;
            }
            Matcher m = Pattern.compile("-?\\d+").matcher(line.substring(line.indexOf(':')));
            long[] p = new long[5];
            for (int k = 0; k < 5 && m.find(); k++) {
                p[k] = Long.parseLong(m.group());
            }
            ing.add(p);
        }
        mejor = 0;
        repartir(0, CUCHARADAS, new long[5], ing, calorias);
        return mejor;
    }

    private static void repartir(int i, int restantes, long[] prop, List<long[]> ing, Long calorias) {
        if (i == ing.size() - 1) { // el último ingrediente se lleva lo que queda
            long[] p = new long[5];
            for (int k = 0; k < 5; k++) {
                p[k] = prop[k] + restantes * ing.get(i)[k];
            }
            if (calorias == null || calorias == p[4]) {
                long puntuacion = 1;
                for (int k = 0; k < 4; k++) {
                    puntuacion *= Math.max(p[k], 0); // un total negativo cuenta como 0
                }
                mejor = Math.max(mejor, puntuacion);
            }
            return;
        }
        for (int cantidad = 0; cantidad <= restantes; cantidad++) {
            long[] nuevas = new long[5];
            for (int k = 0; k < 5; k++) {
                nuevas[k] = prop[k] + cantidad * ing.get(i)[k];
            }
            repartir(i + 1, restantes - cantidad, nuevas, ing, calorias);
        }
    }
}
