package utils_2015;

import java.io.IOException;
import java.util.Map;
import java.util.function.ToIntFunction;
import utils.Utils;

public class Utils_Day16 {
    private static final Map<String, Integer> HUELLA = Map.of("children", 3, "cats", 7, "samoyeds", 2, "pomeranians", 3,
            "akitas", 0, "vizslas", 0, "goldfish", 5, "trees", 3, "cars", 2, "perfumes", 1);

    public static String solvePart1(int year, int day) throws IOException {
        return buscar(year, day, k -> 0);
    }

    public static String solvePart2(int year, int day) throws IOException {
        // cats y trees: mayor que la huella; pomeranians y goldfish: menor
        return buscar(year, day, k -> k.equals("cats") || k.equals("trees") ? 1
                : k.equals("pomeranians") || k.equals("goldfish") ? -1 : 0);
    }

    /** La tía cuyos recuerdos cumplen orden(compuesto) (el signo de su valor menos la huella). */
    private static String buscar(int year, int day, ToIntFunction<String> orden) throws IOException {
        for (String line : Utils.readInput(year, day)) {
            if (line.isBlank()) {
                continue;
            }
            int dosPuntos = line.indexOf(':');
            boolean cumple = true;
            for (String trozo : line.substring(dosPuntos + 1).split(",")) {
                String[] par = trozo.split(":");
                String nombre = par[0].trim();
                int signo = Integer.signum(Integer.parseInt(par[1].trim()) - HUELLA.get(nombre));
                cumple &= signo == orden.applyAsInt(nombre);
            }
            if (cumple) {
                return line.substring(4, dosPuntos);
            }
        }
        return "-";
    }
}
