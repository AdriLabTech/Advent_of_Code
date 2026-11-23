package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day24;

/**
 * DAY 24 2015
 */
public class Day_24_2015 extends Day {

    public Day_24_2015() {
        super(2015, 24);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day24.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day24.solvePart2(year, dayNumber);
    }
}
