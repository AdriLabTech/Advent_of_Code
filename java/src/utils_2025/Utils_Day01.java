package utils_2025;

import java.io.IOException;
import java.util.List;
import utils.Utils;

/**
 * Public Class to implement the Utils for Day 1 of AoC's 2025
 */
public class Utils_Day01 {
    private static final int DIAL = 100; // posiciones del dial (0..99)
    private static final int START = 50; // posición inicial

    public static long solvePart1(int year, int day) throws IOException {
        int puntero = START;
        int contador = 0;

        for (int delta : rotaciones(Utils.readInput(year, day))) {
            puntero = Math.floorMod(puntero + delta, DIAL);
            if (puntero == 0) {
                contador++;
            }
        }
        return contador;
    }

    public static long solvePart2(int year, int day) throws IOException {
        int puntero = START;
        long contador = 0;

        for (int delta : rotaciones(Utils.readInput(year, day))) {
            // Girar a la izquierda equivale a girar a la derecha desde la posición "espejo"
            // (DIAL - puntero). Así solo hay que contar cuántas veces se cruza un múltiplo
            // de 100 hacia delante.
            int inicio = delta > 0 ? puntero : Math.floorMod(DIAL - puntero, DIAL);
            contador += (inicio + Math.abs(delta)) / DIAL;
            puntero = Math.floorMod(puntero + delta, DIAL);
        }
        return contador;
    }

    /**
     * Convierte cada línea (L68, R48...) en un desplazamiento con signo: L =
     * negativo, R = positivo.
     */
    private static List<Integer> rotaciones(List<String> lines) {
        return lines.stream()
                .filter(line -> !line.isBlank())
                .map(line -> (line.charAt(0) == 'L' ? -1 : 1) * Integer.parseInt(line.substring(1).trim()))
                .toList();
    }
}
