# Java

Proyecto Eclipse (Java 21). Arquitectura: `Calendar` (año) y `Day` (día) abstractas; ver `src/core`.

## Ejecutar (desde `java/`)

```bash
javac -d bin $(find src -name '*.java')
java -cp bin core.Main
```

## Inputs
Se leen de `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). No se versionan.

## Añadir un día
1. `src/year_YYYY/Day_NN_YYYY.java` extiende `Day`.
2. Lógica en `src/utils_YYYY/Utils_DayNN.java`.
3. Registrarlo en `src/years/Year_YYYY.java` con `addDay`.
4. Si es un año nuevo, añadirlo en `Main.createCalendar`.
