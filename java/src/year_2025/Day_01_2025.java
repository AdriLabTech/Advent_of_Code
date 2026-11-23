package year_2025;

import core.Day;
import utils_2025.Utils_Day01;

import java.io.IOException;

/**
 * DAY 1 of 2025 AoC
 */
public class Day_01_2025 extends Day {

    public Day_01_2025() {
        super(2025, 1);
    }

    @Override
    public String solvePart1() throws IOException {
        return String.valueOf(Utils_Day01.solvePart1(year, dayNumber));
    }

    @Override
    public String solvePart2() throws IOException {
        return String.valueOf(Utils_Day01.solvePart2(year, dayNumber));
    }
}
