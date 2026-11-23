package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day17;

/**
 * DAY 17 2015
 */
public class Day_17_2015 extends Day {

    public Day_17_2015() {
        super(2015, 17);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day17.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day17.solvePart2(year, dayNumber);
    }
}
