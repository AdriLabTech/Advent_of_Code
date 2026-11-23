package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import utils.Utils;

public class Utils_Day19 {

    public static String solvePart1(int year, int day) throws IOException {
        List<String[]> reemplazos = new ArrayList<>();
        String molecula = leer(Utils.readInput(year, day), reemplazos);
        Set<String> resultados = new HashSet<>();
        for (String[] r : reemplazos) {
            for (int i = molecula.indexOf(r[0]); i >= 0; i = molecula.indexOf(r[0], i + 1)) { // cada aparición
                resultados.add(molecula.substring(0, i) + r[1] + molecula.substring(i + r[0].length()));
            }
        }
        return String.valueOf(resultados.size());
    }

    public static String solvePart2(int year, int day) throws IOException {
        List<String[]> reemplazos = new ArrayList<>();
        String molecula = leer(Utils.readInput(year, day), reemplazos);
        if (!molecula.contains("Rn")) {
            return String.valueOf(pasosBusqueda(reemplazos, molecula));
        }
        // Molécula real: cada reemplazo suma un elemento, salvo los de la forma X => X Rn ... Ar (que
        // añaden Rn y Ar) y los que llevan Y (cada Y añade además una coma y otro elemento). Por eso los
        // pasos son: elementos - (Rn + Ar) - 2 * Y - 1
        long elementos = molecula.chars().filter(Character::isUpperCase).count();
        return String.valueOf(elementos - cuenta(molecula, "Rn") - cuenta(molecula, "Ar") - 2 * cuenta(molecula, "Y") - 1);
    }

    /** Lee los reemplazos 'X => Y' y devuelve la molécula (la última línea que no es un reemplazo). */
    private static String leer(List<String> lines, List<String[]> reemplazos) {
        String molecula = "";
        for (String line : lines) {
            if (line.contains(" => ")) {
                String[] p = line.split(" => ");
                reemplazos.add(new String[] { p[0], p[1].trim() });
            } else if (!line.isBlank()) {
                molecula = line.trim();
            }
        }
        return molecula;
    }

    private static long cuenta(String texto, String trozo) {
        long n = 0;
        for (int i = texto.indexOf(trozo); i >= 0; i = texto.indexOf(trozo, i + 1)) {
            n++;
        }
        return n;
    }

    /** Pasos mínimos de 'e' a la molécula: búsqueda en anchura hacia atrás. Solo sirve para moléculas cortas. */
    private static int pasosBusqueda(List<String[]> reemplazos, String molecula) {
        Set<String> actual = new HashSet<>(Set.of(molecula));
        int pasos = 0;
        while (!actual.contains("e")) {
            pasos++;
            Set<String> siguiente = new HashSet<>();
            for (String m : actual) {
                for (String[] r : reemplazos) {
                    for (int i = m.indexOf(r[1]); i >= 0; i = m.indexOf(r[1], i + 1)) {
                        String nueva = m.substring(0, i) + r[0] + m.substring(i + r[1].length());
                        if (!r[0].equals("e") || nueva.equals("e")) { // 'e' solo vale como paso final
                            siguiente.add(nueva);
                        }
                    }
                }
            }
            actual = siguiente;
        }
        return pasos;
    }
}
