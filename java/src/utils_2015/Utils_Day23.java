package utils_2015;

import java.io.IOException;
import java.util.List;
import utils.Utils;

public class Utils_Day23 {

    public static String solvePart1(int year, int day) throws IOException {
        List<String> lines = Utils.readInput(year, day);
        long[] r = ejecutar(lines, 0);
        long instrucciones = lines.stream().filter(l -> !l.isBlank()).count();
        // el ejemplo del enunciado (4 instrucciones) deja el resultado en a
        return String.valueOf(instrucciones > 4 ? r[1] : r[0]);
    }

    public static String solvePart2(int year, int day) throws IOException {
        return String.valueOf(ejecutar(Utils.readInput(year, day), 1)[1]);
    }

    /** Ejecuta el programa hasta salirse de él y devuelve los registros {a, b}. */
    private static long[] ejecutar(List<String> lines, long a) {
        String[][] programa = lines.stream().filter(l -> !l.isBlank()).map(l -> l.replace(",", "").trim().split("\\s+"))
                .toArray(String[][]::new);
        long[] registros = { a, 0 };
        int pc = 0;
        while (pc >= 0 && pc < programa.length) {
            String[] i = programa[pc];
            int salto = 1;
            switch (i[0]) {
                case "hlf" -> registros[reg(i[1])] /= 2;
                case "tpl" -> registros[reg(i[1])] *= 3;
                case "inc" -> registros[reg(i[1])]++;
                case "jmp" -> salto = Integer.parseInt(i[1]);
                case "jie" -> {
                    if (registros[reg(i[1])] % 2 == 0) {
                        salto = Integer.parseInt(i[2]);
                    }
                }
                case "jio" -> {
                    if (registros[reg(i[1])] == 1) {
                        salto = Integer.parseInt(i[2]);
                    }
                }
                default -> throw new IllegalArgumentException("instrucción desconocida: " + i[0]);
            }
            pc += salto;
        }
        return registros;
    }

    private static int reg(String r) {
        return r.equals("b") ? 1 : 0;
    }
}
