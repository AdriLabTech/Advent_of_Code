package utils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Utils {
    // ==========|| Generals Methods ||==========//

    /**
     * Carpeta común de inputs (compartida por todos los lenguajes): inputs/ en la raíz del repo.
     * Orden: variable AOC_INPUTS_DIR; si no, se busca "inputs" subiendo desde el directorio actual.
     */
    private static Path inputsDir() {
        String env = System.getenv("AOC_INPUTS_DIR");
        if (env != null && !env.isEmpty()) {
            return Paths.get(env);
        }
        for (Path dir = Paths.get("").toAbsolutePath(); dir != null; dir = dir.getParent()) {
            if (Files.isDirectory(dir.resolve("inputs"))) {
                return dir.resolve("inputs");
            }
        }
        return Paths.get("..", "inputs");
    }

    /**
     * read the inputs and save in a String ArrayList
     * 
     * @param year -> Number year of calendar
     * @param day  -> Day number
     * @return -> a String ArrayList
     * @throws IOException -> If the path dont match
     */
    public static List<String> readInput(int year, int day) throws IOException {
        Path path = inputsDir().resolve(String.valueOf(year)).resolve(String.format("day%02d.txt", day));
        return Files.readAllLines(path);
    }

    /**
     * read the inputs and save in a Integer and Integer list Map
     * 
     * @param year -> Number year of calendar
     * @param day  -> Day number
     * @return -> a Map Integer
     * @throws IOException -> If the path dont match
     */
    public static Map<Integer, List<Integer>> readInputMap(int year, int day) throws IOException {
        List<String> lines = readInput(year, day);

        Map<Integer, List<Integer>> filas = new HashMap<>();

        for (String line : lines) {
            String[] partes = line.split(",");
            int x = Integer.parseInt(partes[0].trim());
            int y = Integer.parseInt(partes[1].trim());

            filas.computeIfAbsent(y, k -> new ArrayList<>()).add(x);
        }

        for (List<Integer> xs : filas.values()) {
            Collections.sort(xs);
        }

        return filas;
    }
}