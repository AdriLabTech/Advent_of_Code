package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day12;

/**
 * DAY 12 2015
 */
public class Day_12_2015 extends Day {

    public Day_12_2015() {
        super(2015, 12);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day12.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day12.solvePart2(year, dayNumber);
    }
}
