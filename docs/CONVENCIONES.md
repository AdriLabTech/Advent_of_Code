# Convenciones del repositorio

Todos los lenguajes comparten la misma disposición de datos y el mismo contrato de ejecución.

## Estructura

```
Advent_of_Code/
├── java/  python/  rust/  csharp/  cpp/   # un directorio por lenguaje (autocontenido)
├── scripts/new_day.py                     # generador de esqueletos de día
├── inputs/<año>/dayNN.txt                 # LOCAL, ignorado por git
├── enunciados/<año>/dayNN.md              # LOCAL, ignorado por git
├── docs/                                  # documentación común
├── .githooks/pre-commit                   # bloquea enunciados/inputs
├── LICENSE
└── README.md
```

## Regla de oro: enunciados e inputs NO se suben

Las normas de Advent of Code prohíben redistribuir los textos de los puzzles y los inputs.

- `enunciados/` e `inputs/` están en `.gitignore` (en la raíz y en cualquier subcarpeta).
- `.githooks/pre-commit` rechaza el commit si algún fichero de esas rutas llega al área de staging. Se activa con:
  `git config core.hooksPath .githooks` (ya hecho en este clon; repítelo en clones nuevos).
- Los README no deben copiar texto de los enunciados. Enlazar a `https://adventofcode.com/<año>/day/<n>` está permitido.
- Comprobación rápida: `git check-ignore -v enunciados/2025/day01.md inputs/2025/day01.txt`

## Nomenclatura

- Año: 4 dígitos (`2025`). Día: 2 dígitos (`day01` … `day25`).
- Input: `inputs/<año>/dayNN.txt`. Enunciado: `enunciados/<año>/dayNN.md`.

## Contrato de cada lenguaje

1. Vive en su propio directorio, con el estilo que mejor encaje con el lenguaje (POO, funciones libres, reflexión, macros…).
2. **Un día nuevo = un fichero** (Java: dos, con registro automático por el generador). Sin tocar el núcleo.
3. Cada día expone `part1` y `part2`; devuelven el resultado o «pendiente» (`None`/`null`/`nullopt`/`"-"`).
4. El ejecutor acepta `<año> [día] [--example]`: sin día ejecuta el año completo y muestra resultado y tiempo. (`--example` no existe en Java.)
5. Lee el input de `inputs/<año>/dayNN.txt` (o `dayNN.example.txt`), o de `AOC_INPUTS_DIR`.
6. Tiene una plantilla en `<lenguaje>/templates/` con los marcadores `{{YEAR}}`, `{{DAY}}` (2 dígitos) y `{{DAYNUM}}`, y un caso en `scripts/new_day.py`.
7. Sus artefactos de compilación están en `.gitignore`.
8. Tiene un README propio con requisitos, estructura, cómo crear un día y cómo ejecutar.

## Añadir un lenguaje nuevo

1. Crear `<lenguaje>/` con núcleo, ejecutor y plantilla siguiendo el contrato.
2. Registrar su generador en `scripts/new_day.py` (`GENERATORS`).
3. Añadir sus artefactos de compilación a `.gitignore`.
4. Añadir una columna a las tablas de progreso del README raíz.
