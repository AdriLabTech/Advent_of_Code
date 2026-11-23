package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day10;

/**
 * DAY 10 2015
 */
public class Day_10_2015 extends Day {

    public Day_10_2015() {
        super(2015, 10);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day10.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day10.solvePart2(year, dayNumber);
    }
}
