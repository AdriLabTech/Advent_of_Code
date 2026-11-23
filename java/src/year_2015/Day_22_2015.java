package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day22;

/**
 * DAY 22 2015
 */
public class Day_22_2015 extends Day {

    public Day_22_2015() {
        super(2015, 22);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day22.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day22.solvePart2(year, dayNumber);
    }
}
