package utils_2015;

import java.io.IOException;
import utils.Utils;

public class Utils_Day20 {

    public static String solvePart1(int year, int day) throws IOException {
        return String.valueOf(primeraCasa(Long.parseLong(Utils.readInput(year, day).get(0).trim()), 10, 0));
    }

    public static String solvePart2(int year, int day) throws IOException {
        // cada elfo reparte 11 veces su número y solo a 50 casas
        return String.valueOf(primeraCasa(Long.parseLong(Utils.readInput(year, day).get(0).trim()), 11, 50));
    }

    /** regalos[c] = presentes que recibe la casa c (criba: cada elfo recorre sus casas); casasPorElfo 0 = sin límite. */
    private static long[] regalos(int limite, int porElfo, int casasPorElfo) {
        long[] casas = new long[limite + 1];
        for (int elfo = 1; elfo <= limite; elfo++) {
            long ultima = casasPorElfo > 0 ? Math.min(limite, (long) elfo * casasPorElfo) : limite;
            for (long casa = elfo; casa <= ultima; casa += elfo) {
                casas[(int) casa] += (long) porElfo * elfo;
            }
        }
        return casas;
    }

    private static int primeraCasa(long objetivo, int porElfo, int casasPorElfo) {
        for (int limite = 1 << 14;; limite *= 2) { // si no aparece, se duplica el rango y se vuelve a cribar
            long[] casas = regalos(limite, porElfo, casasPorElfo);
            for (int c = 0; c < casas.length; c++) {
                if (casas[c] >= objetivo) {
                    return c;
                }
            }
        }
    }
}
