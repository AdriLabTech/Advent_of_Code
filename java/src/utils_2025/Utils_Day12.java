package utils_2025;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeSet;
import utils.Utils;

public class Utils_Day12 {

    public static String solvePart1(int year, int day) throws IOException {
        // Formas ('0:' + filas) y regiones ('AxB: q0 q1 ...')
        Map<Integer, List<int[]>> formas = new HashMap<>();
        List<int[]> regiones = new ArrayList<>(); // {ancho, alto, q0, q1, ...}
        List<String> bloque = new ArrayList<>();
        List<String> lines = new ArrayList<>(Utils.readInput(year, day));
        lines.add("");
        for (String line : lines) {
            if (!line.isBlank()) {
                bloque.add(line);
                continue;
            }
            if (bloque.isEmpty()) {
                continue;
            }
            if (bloque.get(0).endsWith(":")) {
                List<int[]> celdas = new ArrayList<>();
                for (int r = 1; r < bloque.size(); r++) {
                    for (int c = 0; c < bloque.get(r).length(); c++) {
                        if (bloque.get(r).charAt(c) == '#') {
                            celdas.add(new int[] { r - 1, c });
                        }
                    }
                }
                formas.put(Integer.parseInt(bloque.get(0).substring(0, bloque.get(0).length() - 1)), celdas);
            } else {
                for (String linea : bloque) {
                    String[] p = linea.split(":");
                    String[] tam = p[0].split("x");
                    String[] q = p[1].trim().split("\\s+");
                    int[] region = new int[2 + q.length];
                    region[0] = Integer.parseInt(tam[0]);
                    region[1] = Integer.parseInt(tam[1]);
                    for (int i = 0; i < q.length; i++) {
                        region[2 + i] = Integer.parseInt(q[i]);
                    }
                    regiones.add(region);
                }
            }
            bloque.clear();
        }

        Map<Integer, List<int[][]>> orient = new HashMap<>();
        for (Map.Entry<Integer, List<int[]>> f : formas.entrySet()) {
            orient.put(f.getKey(), orientaciones(f.getValue()));
        }

        int total = 0;
        for (int[] region : regiones) {
            int ancho = region[0];
            int alto = region[1];
            int piezas = 0;
            int celdas = 0;
            for (int i = 2; i < region.length; i++) {
                piezas += region[i];
                celdas += region[i] * formas.get(i - 2).size();
            }
            if (celdas > ancho * alto) {
                continue; // no caben ni sin huecos
            }
            if (piezas <= (ancho / 3) * (alto / 3)) {
                total++; // cada pieza cabe en un cuadrado de 3x3 y hay sitio para todos esos cuadrados
                continue;
            }
            Tablero t = new Tablero(ancho, alto, Arrays.copyOfRange(region, 2, region.length), orient);
            if (t.resolver(0, ancho * alto - celdas)) {
                total++;
            }
        }
        return String.valueOf(total);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return "-"; // pendiente: la parte 2 se desbloquea al completar el resto de días
    }

    /**
     * Las rotaciones y reflejos distintos de una forma, normalizados a la esquina
     * superior izquierda.
     */
    private static List<int[][]> orientaciones(List<int[]> forma) {
        TreeSet<String> vistas = new TreeSet<>();
        List<int[][]> resultado = new ArrayList<>();
        List<int[]> celdas = forma;
        for (int giro = 0; giro < 4; giro++) {
            List<int[]> rotadas = new ArrayList<>();
            for (int[] p : celdas) {
                rotadas.add(new int[] { p[1], -p[0] }); // rotar 90°
            }
            celdas = rotadas;
            for (int espejo = 0; espejo < 2; espejo++) {
                int menorR = Integer.MAX_VALUE;
                int menorC = Integer.MAX_VALUE;
                List<int[]> f = new ArrayList<>();
                for (int[] p : celdas) {
                    f.add(new int[] { p[0], espejo == 0 ? p[1] : -p[1] });
                }
                for (int[] p : f) {
                    menorR = Math.min(menorR, p[0]);
                    menorC = Math.min(menorC, p[1]);
                }
                int[][] normal = new int[f.size()][];
                for (int i = 0; i < f.size(); i++) {
                    normal[i] = new int[] { f.get(i)[0] - menorR, f.get(i)[1] - menorC };
                }
                Arrays.sort(normal, (x, y) -> x[0] != y[0] ? Integer.compare(x[0], y[0]) : Integer.compare(x[1], y[1]));
                if (vistas.add(Arrays.deepToString(normal))) {
                    resultado.add(normal);
                }
            }
        }
        return resultado;
    }

    private static class Tablero {
        private final int ancho;
        private final int alto;
        private final boolean[] libres;
        private final int[] restantes;
        private final Map<Integer, List<int[][]>> orient;

        Tablero(int ancho, int alto, int[] cantidades, Map<Integer, List<int[][]>> orient) {
            this.ancho = ancho;
            this.alto = alto;
            this.libres = new boolean[ancho * alto];
            Arrays.fill(libres, true);
            this.restantes = cantidades;
            this.orient = orient;
        }

        /**
         * Rellena la primera celda libre (por filas) con una pieza o la deja vacía (si
         * queda holgura).
         */
        boolean resolver(int pos, int hueco) {
            while (pos < ancho * alto && !libres[pos]) {
                pos++;
            }
            if (pos == ancho * alto) {
                return Arrays.stream(restantes).allMatch(q -> q == 0);
            }
            int r0 = pos / ancho;
            int c0 = pos % ancho;
            for (int i = 0; i < restantes.length; i++) {
                if (restantes[i] == 0) {
                    continue;
                }
                for (int[][] forma : orient.get(i)) {
                    // la primera celda de la forma (por filas) es la que se apoya en la celda libre
                    int[] destino = new int[forma.length];
                    boolean cabe = true;
                    for (int k = 0; k < forma.length && cabe; k++) {
                        int r = r0 + forma[k][0] - forma[0][0];
                        int c = c0 + forma[k][1] - forma[0][1];
                        cabe = r >= 0 && c >= 0 && r < alto && c < ancho && libres[r * ancho + c];
                        destino[k] = r * ancho + c;
                    }
                    if (!cabe) {
                        continue;
                    }
                    for (int d : destino) {
                        libres[d] = false;
                    }
                    restantes[i]--;
                    if (resolver(pos + 1, hueco)) {
                        return true;
                    }
                    restantes[i]++;
                    for (int d : destino) {
                        libres[d] = true;
                    }
                }
            }
            if (hueco > 0) {
                libres[pos] = false; // dejar esta celda vacía
                if (resolver(pos + 1, hueco - 1)) {
                    return true;
                }
                libres[pos] = true;
            }
            return false;
        }
    }
}
