# C#

Estado: **sin empezar** (estructura preparada, ningún día resuelto).

Sigue el contrato de [../docs/CONVENCIONES.md](../docs/CONVENCIONES.md):

- Input: `../inputs/<año>/dayNN.txt` (o `AOC_INPUTS_DIR`). No se versiona.
- Cada día expone `part1` y `part2` y devuelve texto.
- Ejecutor por año/día con tiempo de ejecución.

## Requisitos
- .NET SDK 8+

## Estructura sugerida
```
csharp/
├── AdventOfCode.csproj
└── Y2025/Day01.cs
```
Ejecución prevista: `dotnet run -c Release -- 2025 1`
