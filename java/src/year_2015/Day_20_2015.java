package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day20;

/**
 * DAY 20 2015
 */
public class Day_20_2015 extends Day {

    public Day_20_2015() {
        super(2015, 20);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day20.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day20.solvePart2(year, dayNumber);
    }
}
