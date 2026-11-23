package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day25;

/**
 * DAY 25 2015
 */
public class Day_25_2015 extends Day {

    public Day_25_2015() {
        super(2015, 25);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day25.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day25.solvePart2(year, dayNumber);
    }
}
