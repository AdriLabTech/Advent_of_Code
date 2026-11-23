package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day19;

/**
 * DAY 19 2015
 */
public class Day_19_2015 extends Day {

    public Day_19_2015() {
        super(2015, 19);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day19.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day19.solvePart2(year, dayNumber);
    }
}
