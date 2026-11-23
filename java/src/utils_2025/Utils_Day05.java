package utils_2025;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import utils.Utils;

public class Utils_Day05 {

    public static String solvePart1(int year, int day) throws IOException {
        List<long[]> rangos = new ArrayList<>();
        List<Long> ids = new ArrayList<>();
        leer(Utils.readInput(year, day), rangos, ids);

        long frescos = 0;
        for (long id : ids) {
            for (long[] rango : rangos) {
                if (rango[0] <= id && id <= rango[1]) {
                    frescos++;
                    break;
                }
            }
        }
        return String.valueOf(frescos);
    }

    public static String solvePart2(int year, int day) throws IOException {
        List<long[]> rangos = new ArrayList<>();
        leer(Utils.readInput(year, day), rangos, new ArrayList<>());

        // unión de rangos: se ordenan y se fusionan los que se solapan o se tocan; luego
        // se suman sus longitudes
        rangos.sort(Comparator.<long[]>comparingLong(r -> r[0]).thenComparingLong(r -> r[1]));
        long total = 0;
        long hasta = -1;
        for (long[] r : rangos) {
            if (r[1] > hasta) {
                total += r[1] - Math.max(r[0], hasta + 1) + 1;
                hasta = r[1];
            }
        }
        return String.valueOf(total);
    }

    /** Rangos frescos 'a-b', línea en blanco y luego los IDs disponibles. */
    private static void leer(List<String> lines, List<long[]> rangos, List<Long> ids) {
        boolean enRangos = true;
        for (String line : lines) {
            if (line.isBlank()) {
                enRangos = false;
            } else if (enRangos) {
                String[] p = line.split("-");
                rangos.add(new long[] { Long.parseLong(p[0].trim()), Long.parseLong(p[1].trim()) });
            } else {
                ids.add(Long.parseLong(line.trim()));
            }
        }
    }
}
