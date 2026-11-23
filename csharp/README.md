# 🟣 C#

Estilo: **POO ligera con descubrimiento por reflexión**. Cada día hereda de `Day`; el año y el día se deducen del namespace y del nombre de la clase (`AdventOfCode.Solutions.Y2025.Day03`), sin registro manual.

Requisitos: .NET SDK 10 (`net10.0`; cambia `TargetFramework` en el `.csproj` si usas otro).

```
csharp/
├── AdventOfCode.csproj
├── Core/
│   ├── Day.cs           # clase base (Part1/Part2)
│   ├── Input.cs         # lectura de inputs, Ints, Paragraphs
│   └── Runner.cs        # descubre y ejecuta los días (Main)
├── Solutions/Y2025/Day03.cs   # una solución = un fichero
└── templates/Day.cs.tpl
```

## Crear un día
```bash
scripts/new_day.py csharp 2025 3     # desde la raíz del repo
```
Edita `Part1(string[] lines)` y `Part2`; devuelven `object?` (`null` = pendiente).

## Ejecutar (desde `csharp/`)
```bash
dotnet run -c Release -- 2025 3
dotnet run -c Release -- 2025             # todo el año
dotnet run -c Release -- 2025 3 --example
```
