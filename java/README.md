# ☕ Java

Estilo: **POO clásica**. `Calendar` (año) y `Day` (día) abstractas en `src/core`; cada año registra sus días.

Requisitos: JDK 21. Proyecto Eclipse (`.project`, `.classpath`) o `javac` a mano.

```
java/
├── src/
│   ├── core/        # Calendar, Day, Main (ejecutor interactivo)
│   ├── utils/       # Utils.readInput
│   ├── years/       # Year_YYYY: registro de días del año
│   ├── year_YYYY/   # Day_NN_YYYY: clase del día
│   └── utils_YYYY/  # Utils_DayNN: lógica de la solución
└── templates/       # plantillas del generador
```

## Crear un día
```bash
scripts/new_day.py java 2025 3       # desde la raíz del repo
```
Crea `Day_03_2025` y `Utils_Day03`, y **registra el día** en `Year_2025` (y el año en `Main` si es nuevo). Escribe la solución en `Utils_Day03.solvePart1/2`, que devuelven `String` (`"-"` = pendiente).

## Ejecutar (desde `java/`)
```bash
javac -d bin $(find src -name '*.java')
java -cp bin core.Main
```
Los inputs se leen de `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). Java no soporta `--example`.
