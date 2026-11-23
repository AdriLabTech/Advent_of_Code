package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day16;

/**
 * DAY 16 2015
 */
public class Day_16_2015 extends Day {

    public Day_16_2015() {
        super(2015, 16);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day16.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day16.solvePart2(year, dayNumber);
    }
}
