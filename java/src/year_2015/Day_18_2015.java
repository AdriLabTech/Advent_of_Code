package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day18;

/**
 * DAY 18 2015
 */
public class Day_18_2015 extends Day {

    public Day_18_2015() {
        super(2015, 18);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day18.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day18.solvePart2(year, dayNumber);
    }
}
