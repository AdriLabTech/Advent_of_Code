package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day23;

/**
 * DAY 23 2015
 */
public class Day_23_2015 extends Day {

    public Day_23_2015() {
        super(2015, 23);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day23.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day23.solvePart2(year, dayNumber);
    }
}
