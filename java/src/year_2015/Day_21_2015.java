package year_2015;

import java.io.IOException;

import core.Day;
import utils_2015.Utils_Day21;

/**
 * DAY 21 2015
 */
public class Day_21_2015 extends Day {

    public Day_21_2015() {
        super(2015, 21);
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day21.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day21.solvePart2(year, dayNumber);
    }
}
