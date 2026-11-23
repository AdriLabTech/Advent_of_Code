package utils_2015;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import utils.Utils;

public class Utils_Day07 {

    public static String solvePart1(int year, int day) throws IOException {
        Map<String, String[]> gates = leer(Utils.readInput(year, day));
        // el ejemplo del enunciado no tiene cable a
        return gates.containsKey("a") ? String.valueOf(valor("a", gates, new HashMap<>(), null, 0)) : "-";
    }

    public static String solvePart2(int year, int day) throws IOException {
        Map<String, String[]> gates = leer(Utils.readInput(year, day));
        if (!gates.containsKey("a")) {
            return "-";
        }
        // la señal de a (parte 1) se pasa al cable b y se recalcula todo
        int a = valor("a", gates, new HashMap<>(), null, 0);
        return String.valueOf(valor("a", gates, new HashMap<>(), "b", a));
    }

    private static Map<String, String[]> leer(List<String> lines) {
        Map<String, String[]> gates = new HashMap<>();
        for (String line : lines) {
            if (!line.isBlank()) {
                String[] p = line.split(" -> ");
                gates.put(p[1].trim(), p[0].trim().split("\\s+"));
            }
        }
        return gates;
    }

    /** Señal de un cable (o número) de 16 bits. {@code forzado} sustituye la señal de un cable. */
    private static int valor(String token, Map<String, String[]> gates, Map<String, Integer> memo, String forzado, int valorForzado) {
        if (Character.isDigit(token.charAt(0))) {
            return Integer.parseInt(token);
        }
        if (token.equals(forzado)) {
            return valorForzado;
        }
        if (memo.containsKey(token)) {
            return memo.get(token);
        }
        String[] g = gates.get(token);
        int resultado;
        if (g.length == 1) { // 123 -> x  /  a -> b
            resultado = valor(g[0], gates, memo, forzado, valorForzado);
        } else if (g.length == 2) { // NOT x
            resultado = ~valor(g[1], gates, memo, forzado, valorForzado) & 0xFFFF;
        } else {
            int a = valor(g[0], gates, memo, forzado, valorForzado);
            int b = valor(g[2], gates, memo, forzado, valorForzado);
            resultado = switch (g[1]) {
                case "AND" -> a & b;
                case "OR" -> a | b;
                case "LSHIFT" -> (a << b) & 0xFFFF;
                default -> a >> b; // RSHIFT
            };
        }
        memo.put(token, resultado);
        return resultado;
    }
}
