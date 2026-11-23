package utils_2025;

import java.io.IOException;
import utils.Utils;

public class Utils_Day03 {

    public static String solvePart1(int year, int day) throws IOException {
        return total(year, day, 2);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return total(year, day, 12);
    }

    private static String total(int year, int day, int cuantas) throws IOException {
        long suma = 0;
        for (String line : Utils.readInput(year, day)) {
            if (!line.isBlank()) {
                suma += mayorJoltaje(line.trim(), cuantas);
            }
        }
        return String.valueOf(suma);
    }

    /**
     * Número más grande que se forma encendiendo {@code cuantas} baterías sin
     * cambiar su orden (voraz).
     */
    private static long mayorJoltaje(String banco, int cuantas) {
        StringBuilder elegidas = new StringBuilder();
        for (int i = 0; i < banco.length(); i++) {
            // una elegida peor que la actual se descarta mientras queden baterías de sobra
            // para completar el número
            while (elegidas.length() > 0 && elegidas.charAt(elegidas.length() - 1) < banco.charAt(i)
                    && elegidas.length() + banco.length() - i > cuantas) {
                elegidas.setLength(elegidas.length() - 1);
            }
            if (elegidas.length() < cuantas) {
                elegidas.append(banco.charAt(i));
            }
        }
        return Long.parseLong(elegidas.toString());
    }
}
