package utils_2015;

import java.io.IOException;
import utils.Utils;

public class Utils_Day10 {

    public static String solvePart1(int year, int day) throws IOException {
        return String.valueOf(mirarYDecir(Utils.readInput(year, day).get(0).trim(), 40));
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(mirarYDecir(Utils.readInput(year, day).get(0).trim(), 50));
    }

    /** Cada tanda de dígitos iguales se sustituye por (cuántos)(qué dígito). */
    private static int mirarYDecir(String texto, int veces) {
        String actual = texto;
        for (int v = 0; v < veces; v++) {
            StringBuilder siguiente = new StringBuilder(actual.length() * 2);
            int i = 0;
            while (i < actual.length()) {
                int j = i;
                while (j < actual.length() && actual.charAt(j) == actual.charAt(i)) {
                    j++;
                }
                siguiente.append(j - i).append(actual.charAt(i));
                i = j;
            }
            actual = siguiente.toString();
        }
        return actual.length();
    }
}
