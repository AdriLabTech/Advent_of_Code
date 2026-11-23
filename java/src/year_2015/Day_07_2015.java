package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day07;

/**
 * DAY 7 2015
 */
public class Day_07_2015 extends Day {

    public Day_07_2015() {
        super(2015, 7);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day07.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day07.solvePart2(year, dayNumber);
    }
}
