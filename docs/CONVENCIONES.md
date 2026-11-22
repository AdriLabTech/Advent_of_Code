# Convenciones del repositorio

Todos los lenguajes comparten la misma disposición de datos y el mismo contrato de ejecución.

## Estructura

```
Advent_of_Code/
├── java/  python/  rust/  csharp/  cpp/   # un directorio por lenguaje (autocontenido)
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

1. Vive en su propio directorio y se compila/ejecuta desde él (`cd <lenguaje>`).
2. Lee el input de `../inputs/<año>/dayNN.txt`, o de la ruta indicada por la variable `AOC_INPUTS_DIR`.
3. Cada día expone `part1` y `part2` y devuelve el resultado como texto.
4. Hay un ejecutor que acepta año y día (o el año completo) y muestra resultado y tiempo.
5. Sus artefactos de compilación están ignorados por git.
6. Tiene un README propio con requisitos, cómo ejecutar y cómo añadir un día.

## Añadir un lenguaje nuevo

1. Crear `<lenguaje>/` con su README siguiendo el contrato anterior.
2. Añadir sus artefactos de compilación a `.gitignore`.
3. Añadir una columna al progreso del README raíz.
