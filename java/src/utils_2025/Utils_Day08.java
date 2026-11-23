package utils_2025;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import utils.Utils;

public class Utils_Day08 {

    private static final int CONEXIONES = 1000; // pares más cercanos que se conectan en la parte 1
    private static final int CONEXIONES_EJEMPLO = 10; // el ejemplo del enunciado (20 cajas) conecta solo 10

    public static long solvePart1(int year, int day) throws IOException {
        int[][] cajas = leer(Utils.readInput(year, day));
        int[] tamanos = conectar(cajas, cajas.length <= 20 ? CONEXIONES_EJEMPLO : CONEXIONES, null);

        // Producto de los tres circuitos más grandes
        List<Integer> circuitos = new ArrayList<>();
        for (int t : tamanos) {
            if (t > 0) {
                circuitos.add(t);
            }
        }
        circuitos.sort(Collections.reverseOrder());
        long result = 1;
        for (int i = 0; i < Math.min(3, circuitos.size()); i++) {
            result *= circuitos.get(i);
        }
        return result;
    }

    public static long solvePart2(int year, int day) throws IOException {
        int[][] cajas = leer(Utils.readInput(year, day));
        int[] ultimo = new int[2];
        conectar(cajas, -1, ultimo); // la última unión es la que deja un solo circuito
        return (long) cajas[ultimo[0]][0] * cajas[ultimo[1]][0];
    }

    private static int[][] leer(List<String> lines) {
        List<int[]> cajas = new ArrayList<>();
        for (String line : lines) {
            if (!line.isBlank()) {
                String[] p = line.split(",");
                cajas.add(new int[] { Integer.parseInt(p[0].trim()), Integer.parseInt(p[1].trim()),
                        Integer.parseInt(p[2].trim()) });
            }
        }
        return cajas.toArray(new int[0][]);
    }

    /**
     * Recorre los pares por distancia creciente (Kruskal) y une los circuitos de
     * cada par. Se detiene tras {@code limitePares} pares (cuenten o no como unión;
     * -1 = sin límite) o al quedar un solo circuito. Devuelve el tamaño de cada
     * circuito (0 si no es raíz) y deja en {@code ultimo} el último par que unió dos
     * circuitos distintos.
     */
    private static int[] conectar(int[][] cajas, int limitePares, int[] ultimo) {
        int n = cajas.length;
        List<Pair> pares = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long dx = cajas[i][0] - cajas[j][0];
                long dy = cajas[i][1] - cajas[j][1];
                long dz = cajas[i][2] - cajas[j][2];
                pares.add(new Pair(i, j, dx * dx + dy * dy + dz * dz));
            }
        }
        Collections.sort(pares); // estable: empates por orden de generación (i, j)

        int[] parent = new int[n];
        int[] size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
        int circuitos = n;
        for (int visitados = 0; visitados < pares.size(); visitados++) {
            if (visitados == limitePares || circuitos == 1) {
                break;
            }
            Pair p = pares.get(visitados);
            int rootI = find(p.i, parent);
            int rootJ = find(p.j, parent);
            if (rootI != rootJ) { // si ya estaban en el mismo circuito no pasa nada
                if (size[rootI] < size[rootJ]) {
                    parent[rootI] = rootJ;
                    size[rootJ] += size[rootI];
                } else {
                    parent[rootJ] = rootI;
                    size[rootI] += size[rootJ];
                }
                circuitos--;
                if (ultimo != null) {
                    ultimo[0] = p.i;
                    ultimo[1] = p.j;
                }
            }
        }
        int[] tamanos = new int[n];
        for (int i = 0; i < n; i++) {
            tamanos[i] = parent[i] == i ? size[i] : 0;
        }
        return tamanos;
    }

    // Helper class to represent pairs of boxes with their distance
    static class Pair implements Comparable<Pair> {
        int i, j; // Index of the boxes
        long distSQ; // Squared distance between boxes

        Pair(int i, int j, long distSQ) {
            this.i = i;
            this.j = j;
            this.distSQ = distSQ;
        }

        // Compare by distance for sorting
        @Override
        public int compareTo(Pair other) {
            return Long.compare(this.distSQ, other.distSQ);
        }
    }

    /**
     * Finds the representative (root) of the set containing element i.
     * Implements path compression to optimize future operations.
     *
     * @param i      -> the element whose set is being found
     * @param parent -> the parent array representing the forest
     * @return -> the root representative of the set containing i
     */
    public static int find(int i, int[] parent) {
        if (parent[i] != i) {
            parent[i] = find(parent[i], parent);
        }
        return parent[i];
    }
}