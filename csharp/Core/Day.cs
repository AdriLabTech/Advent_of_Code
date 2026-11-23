namespace AdventOfCode.Core;

/// <summary>
/// Base de cada día. Convención (sin registro manual):
///   namespace AdventOfCode.Solutions.Y{año};  class Day{NN} : Day
/// El año y el día se deducen del nombre; el runner los descubre por reflexión.
/// Devolver null = parte pendiente.
/// </summary>
public abstract class Day
{
    public abstract object? Part1(string[] lines);
    public abstract object? Part2(string[] lines);
}
