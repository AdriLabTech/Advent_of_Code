package utils_2015;

import java.io.IOException;
import java.util.List;
import utils.Utils;

public class Utils_Day18 {
    private static final int PASOS = 100;
    private static final int PASOS_EJEMPLO_P1 = 4; // el ejemplo del enunciado (6x6) usa 4 pasos en la parte 1 ...
    private static final int PASOS_EJEMPLO_P2 = 5; // ... y 5 en la parte 2

    public static String solvePart1(int year, int day) throws IOException {
        return String.valueOf(animar(Utils.readInput(year, day), false));
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(animar(Utils.readInput(year, day), true));
    }

    private static int animar(List<String> lines, boolean esquinasFijas) {
        List<String> filas = lines.stream().map(String::trim).filter(l -> !l.isEmpty()).toList();
        int lado = filas.size();
        boolean[][] luces = new boolean[lado][lado];
        for (int r = 0; r < lado; r++) {
            for (int c = 0; c < lado; c++) {
                luces[r][c] = filas.get(r).charAt(c) == '#';
            }
        }
        int pasos = lado <= 6 ? (esquinasFijas ? PASOS_EJEMPLO_P2 : PASOS_EJEMPLO_P1) : PASOS;
        fijar(luces, esquinasFijas);
        for (int i = 0; i < pasos; i++) {
            luces = paso(luces);
            fijar(luces, esquinasFijas);
        }
        int encendidas = 0;
        for (boolean[] fila : luces) {
            for (boolean l : fila) {
                encendidas += l ? 1 : 0;
            }
        }
        return encendidas;
    }

    /** Las cuatro esquinas están atascadas encendidas. */
    private static void fijar(boolean[][] luces, boolean esquinasFijas) {
        if (esquinasFijas) {
            int u = luces.length - 1;
            luces[0][0] = luces[0][u] = luces[u][0] = luces[u][u] = true;
        }
    }

    /** Una generación del juego de la vida (los vecinos fuera de la rejilla cuentan como apagados). */
    private static boolean[][] paso(boolean[][] luces) {
        int lado = luces.length;
        boolean[][] nuevas = new boolean[lado][lado];
        for (int r = 0; r < lado; r++) {
            for (int c = 0; c < lado; c++) {
                int vecinos = 0;
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        int nr = r + dr;
                        int nc = c + dc;
                        if ((dr != 0 || dc != 0) && nr >= 0 && nr < lado && nc >= 0 && nc < lado && luces[nr][nc]) {
                            vecinos++;
                        }
                    }
                }
                nuevas[r][c] = vecinos == 3 || (vecinos == 2 && luces[r][c]);
            }
        }
        return nuevas;
    }
}
