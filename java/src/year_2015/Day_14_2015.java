package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day14;

/**
 * DAY 14 2015
 */
public class Day_14_2015 extends Day {

    public Day_14_2015() {
        super(2015, 14);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day14.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day14.solvePart2(year, dayNumber);
    }
}
