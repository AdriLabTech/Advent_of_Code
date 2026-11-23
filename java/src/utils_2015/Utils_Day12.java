package utils_2015;

import java.io.IOException;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day12 {

    public static String solvePart1(int year, int day) throws IOException {
        Matcher m = Pattern.compile("-?\\d+").matcher(Utils.readInput(year, day).get(0));
        long suma = 0;
        while (m.find()) {
            suma += Long.parseLong(m.group());
        }
        return String.valueOf(suma);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(sumaSinRojos(Utils.readInput(year, day).get(0)));
    }

    /** Un nivel de la pila: {suma, esObjeto (0/1), tieneRojo (0/1)}. */
    private static long sumaSinRojos(String t) {
        // Suma de todos los números ignorando los objetos {...} que tengan algún valor "red"
        // (los arrays no cuentan como objeto). Cada { o [ abre un nivel con su suma; al cerrarlo
        // se suma al nivel de fuera (salvo un objeto con "red", que aporta 0).
        Deque<long[]> pila = new ArrayDeque<>();
        pila.push(new long[] { 0, 0, 0 });
        for (int i = 0; i < t.length(); i++) {
            char c = t.charAt(i);
            if (c == '{' || c == '[') {
                pila.push(new long[] { 0, c == '{' ? 1 : 0, 0 });
            } else if (c == '}' || c == ']') {
                long[] n = pila.pop();
                pila.peek()[0] += n[2] == 1 ? 0 : n[0];
            } else if (c == '"') {
                int fin = t.indexOf('"', i + 1);
                boolean esClave = fin + 1 < t.length() && t.charAt(fin + 1) == ':'; // un ':' detrás = clave
                if (t.substring(i + 1, fin).equals("red") && pila.peek()[1] == 1 && !esClave) {
                    pila.peek()[2] = 1;
                }
                i = fin;
            } else if (c == '-' || Character.isDigit(c)) {
                int fin = i + 1;
                while (fin < t.length() && Character.isDigit(t.charAt(fin))) {
                    fin++;
                }
                pila.peek()[0] += Long.parseLong(t.substring(i, fin));
                i = fin - 1;
            }
        }
        return pila.pop()[0];
    }
}
