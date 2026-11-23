package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day15;

/**
 * DAY 15 2015
 */
public class Day_15_2015 extends Day {

    public Day_15_2015() {
        super(2015, 15);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day15.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day15.solvePart2(year, dayNumber);
    }
}
