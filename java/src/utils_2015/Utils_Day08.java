package utils_2015;

import java.io.IOException;
import java.util.List;
import utils.Utils;

public class Utils_Day08 {

    public static String solvePart1(int year, int day) throws IOException {
        long total = 0;
        for (String literal : literales(Utils.readInput(year, day))) {
            total += literal.length() - enMemoria(literal);
        }
        return String.valueOf(total);
    }

    public static String solvePart2(int year, int day) throws IOException {
        long total = 0;
        for (String literal : literales(Utils.readInput(year, day))) {
            total += codificado(literal) - literal.length();
        }
        return String.valueOf(total);
    }

    private static List<String> literales(List<String> lines) {
        return lines.stream().map(String::trim).filter(l -> !l.isEmpty()).toList();
    }

    /** Caracteres del valor de un literal: cada escape (\\, \", \xNN) cuenta como uno; las comillas exteriores no cuentan. */
    private static int enMemoria(String literal) {
        String c = literal.substring(1, literal.length() - 1);
        int i = 0;
        int n = 0;
        while (i < c.length()) {
            i += c.charAt(i) == '\\' ? (c.charAt(i + 1) == 'x' ? 4 : 2) : 1;
            n++;
        }
        return n;
    }

    /** Caracteres de la cadena codificada de nuevo: comillas exteriores y \ y " escapadas. */
    private static int codificado(String literal) {
        return literal.length() + 2 + (int) literal.chars().filter(c -> c == '\\' || c == '"').count();
    }
}
