package utils_2015;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import utils.Utils;

public class Utils_Day13 {
    private static int mejor;

    public static String solvePart1(int year, int day) throws IOException {
        Map<String, Integer> felicidad = new HashMap<>();
        List<String> invitados = new ArrayList<>();
        leer(Utils.readInput(year, day), felicidad, invitados);
        return String.valueOf(mejorMesa(felicidad, invitados));
    }

    public static String solvePart2(int year, int day) throws IOException {
        Map<String, Integer> felicidad = new HashMap<>();
        List<String> invitados = new ArrayList<>();
        leer(Utils.readInput(year, day), felicidad, invitados);
        invitados.add("Yo"); // yo me siento con felicidad 0 con todos
        return String.valueOf(mejorMesa(felicidad, invitados));
    }

    /** 'A would gain/lose N happiness units by sitting next to B.' -> felicidad["A|B"]. */
    private static void leer(List<String> lines, Map<String, Integer> felicidad, List<String> invitados) {
        for (String line : lines) {
            if (line.isBlank()) {
                continue;
            }
            String[] p = line.replaceAll("\\.$", "").trim().split(" ");
            int n = Integer.parseInt(p[3]);
            felicidad.put(p[0] + "|" + p[p.length - 1], p[2].equals("gain") ? n : -n);
            if (!invitados.contains(p[0])) {
                invitados.add(p[0]);
            }
        }
    }

    /** Mayor suma de felicidad en una mesa redonda (cada pareja de vecinos cuenta en los dos sentidos). */
    private static int mejorMesa(Map<String, Integer> f, List<String> invitados) {
        Collections.sort(invitados);
        int n = invitados.size();
        int[][] valor = new int[n][n];
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                valor[a][b] = f.getOrDefault(invitados.get(a) + "|" + invitados.get(b), 0)
                        + f.getOrDefault(invitados.get(b) + "|" + invitados.get(a), 0);
            }
        }
        int[] mesa = new int[n];
        for (int i = 0; i < n; i++) {
            mesa[i] = i;
        }
        mejor = Integer.MIN_VALUE;
        permutar(mesa, 1, valor); // la mesa es circular: fijar el primero evita repetir giros
        return mejor;
    }

    private static void permutar(int[] mesa, int desde, int[][] valor) {
        if (desde == mesa.length) {
            int total = 0;
            for (int i = 0; i < mesa.length; i++) {
                total += valor[mesa[i]][mesa[(i + 1) % mesa.length]];
            }
            mejor = Math.max(mejor, total);
            return;
        }
        for (int i = desde; i < mesa.length; i++) {
            int t = mesa[desde];
            mesa[desde] = mesa[i];
            mesa[i] = t;
            permutar(mesa, desde + 1, valor);
            t = mesa[desde];
            mesa[desde] = mesa[i];
            mesa[i] = t;
        }
    }
}
