package utils_2015;

import java.io.IOException;
import java.util.HashSet;
import java.util.Set;
import utils.Utils;

public class Utils_Day11 {
    private static final String PROHIBIDAS = "iol";

    public static String solvePart1(int year, int day) throws IOException {
        return siguienteClave(Utils.readInput(year, day).get(0).trim());
    }

    public static String solvePart2(int year, int day) throws IOException {
        return siguienteClave(siguienteClave(Utils.readInput(year, day).get(0).trim()));
    }

    private static String siguienteClave(String clave) {
        char[] c = clave.toCharArray();
        do {
            incrementar(c);
        } while (!esValida(c));
        return new String(c);
    }

    /**
     * Suma uno como si fuera un número en base 26 (z pasa a a y acarrea). Salta de
     * golpe las que tienen i, o o l.
     */
    private static void incrementar(char[] clave) {
        for (int i = 0; i < clave.length; i++) {
            if (PROHIBIDAS.indexOf(clave[i]) >= 0) { // todo lo que va detrás se pone a 'a'
                clave[i]++;
                for (int k = i + 1; k < clave.length; k++) {
                    clave[k] = 'a';
                }
                return;
            }
        }
        for (int k = clave.length - 1; k >= 0; k--) {
            if (clave[k] == 'z') {
                clave[k] = 'a';
            } else {
                clave[k]++;
                return;
            }
        }
    }

    private static boolean esValida(char[] c) {
        boolean escalera = false;
        boolean sinProhibidas = true;
        Set<Character> dobles = new HashSet<>(); // letras distintas dobles
        for (int i = 0; i < c.length; i++) {
            sinProhibidas &= PROHIBIDAS.indexOf(c[i]) < 0;
            if (i + 2 < c.length) {
                escalera |= c[i] + 1 == c[i + 1] && c[i + 1] + 1 == c[i + 2];
            }
            if (i + 1 < c.length && c[i] == c[i + 1]) {
                dobles.add(c[i]);
            }
        }
        return escalera && sinProhibidas && dobles.size() >= 2;
    }
}
