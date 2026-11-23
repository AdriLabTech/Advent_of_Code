package utils_2025;

import java.io.IOException;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import utils.Utils;

public class Utils_Day02 {

    public static String solvePart1(int year, int day) throws IOException {
        // ID inválido = un bloque repetido exactamente dos veces: periodo = mitad de los dígitos
        BigInteger total = BigInteger.ZERO;
        for (long[] rango : rangos(Utils.readInput(year, day))) {
            for (int largo = 2; largo <= String.valueOf(rango[1]).length(); largo += 2) {
                total = total.add(sumaConPeriodo(rango[0], rango[1], largo, largo / 2));
            }
        }
        return total.toString();
    }

    public static String solvePart2(int year, int day) throws IOException {
        // Ahora vale cualquier número de repeticiones (>= 2): un periodo p < largo que divida al largo.
        // Un mismo número puede tener varios periodos (111111 -> 1, 2 y 3), así que se suma por periodo
        // mínimo exacto: g[p] = (números con periodo p) - (los que ya tienen un periodo menor que divide a p)
        BigInteger total = BigInteger.ZERO;
        for (long[] rango : rangos(Utils.readInput(year, day))) {
            for (int largo = 2; largo <= String.valueOf(rango[1]).length(); largo++) {
                List<int[]> periodos = new ArrayList<>();
                List<BigInteger> sumas = new ArrayList<>();
                for (int p = 1; p < largo; p++) {
                    if (largo % p != 0) {
                        continue;
                    }
                    BigInteger valor = sumaConPeriodo(rango[0], rango[1], largo, p);
                    for (int i = 0; i < periodos.size(); i++) {
                        if (p % periodos.get(i)[0] == 0) {
                            valor = valor.subtract(sumas.get(i));
                        }
                    }
                    periodos.add(new int[] { p });
                    sumas.add(valor);
                }
                for (BigInteger suma : sumas) {
                    total = total.add(suma);
                }
            }
        }
        return total.toString();
    }

    /**
     * Suma de los números de {@code largo} dígitos en [a, b] formados repitiendo un
     * bloque de {@code periodo} dígitos.
     */
    private static BigInteger sumaConPeriodo(long a, long b, int largo, int periodo) {
        BigInteger diezLargo = BigInteger.TEN.pow(largo);
        BigInteger diezPeriodo = BigInteger.TEN.pow(periodo);
        BigInteger desde = BigInteger.valueOf(a).max(BigInteger.TEN.pow(largo - 1));
        BigInteger hasta = BigInteger.valueOf(b).min(diezLargo.subtract(BigInteger.ONE));
        BigInteger m = diezLargo.subtract(BigInteger.ONE).divide(diezPeriodo.subtract(BigInteger.ONE)); // n = x * m
        BigInteger menor = BigInteger.TEN.pow(periodo - 1).max(desde.add(m).subtract(BigInteger.ONE).divide(m));
        BigInteger mayor = diezPeriodo.subtract(BigInteger.ONE).min(hasta.divide(m));
        if (menor.compareTo(mayor) > 0) {
            return BigInteger.ZERO;
        }
        return m.multiply(menor.add(mayor)).multiply(mayor.subtract(menor).add(BigInteger.ONE)).shiftRight(1);
    }

    /** Líneas 'a-b,c-d,...' como lista de {a, b}. */
    private static List<long[]> rangos(List<String> lines) {
        List<long[]> rangos = new ArrayList<>();
        for (String line : lines) {
            for (String r : line.split(",")) {
                if (!r.isBlank()) {
                    String[] p = r.trim().split("-");
                    rangos.add(new long[] { Long.parseLong(p[0]), Long.parseLong(p[1]) });
                }
            }
        }
        return rangos;
    }
}
