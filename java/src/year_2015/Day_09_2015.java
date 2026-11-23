package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day09;

/**
 * DAY 9 2015
 */
public class Day_09_2015 extends Day {

    public Day_09_2015() {
        super(2015, 9);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day09.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day09.solvePart2(year, dayNumber);
    }
}
