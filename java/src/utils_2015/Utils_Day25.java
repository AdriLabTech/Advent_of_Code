package utils_2015;

import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import utils.Utils;

public class Utils_Day25 {
    private static final long PRIMER_CODIGO = 20151125L;
    private static final long MULTIPLICADOR = 252533L;
    private static final long MODULO = 33554393L;

    public static String solvePart1(int year, int day) throws IOException {
        Matcher m = Pattern.compile("\\d+").matcher(Utils.readInput(year, day).get(0));
        m.find();
        long fila = Long.parseLong(m.group());
        m.find();
        return String.valueOf(codigo(fila, Long.parseLong(m.group())));
    }

    public static String solvePart2(int year, int day) throws IOException {
        return "-"; // la parte 2 es la estrella final gratuita (no tiene puzzle)
    }

    /**
     * Código de la casilla (fila, columna): el papel se rellena por diagonales, así que
     * primero se halla el número de orden n de la casilla y luego se aplica n-1 veces el
     * generador (con potencia modular, sin bucle).
     */
    private static long codigo(long fila, long columna) {
        long diagonal = fila + columna - 1; // las anteriores contienen 1 + 2 + ... + (diagonal-1) casillas
        long n = (diagonal - 1) * diagonal / 2 + columna;
        long base = MULTIPLICADOR;
        long exponente = n - 1;
        long resultado = 1;
        for (; exponente > 0; exponente >>= 1, base = base * base % MODULO) {
            if ((exponente & 1) == 1) {
                resultado = resultado * base % MODULO;
            }
        }
        return PRIMER_CODIGO * resultado % MODULO;
    }
}
