package year_{{YEAR}};

import java.io.IOException;

import core.Day;
import utils_{{YEAR}}.Utils_Day{{DAY}};

/**
 * DAY {{DAYNUM}} {{YEAR}}
 */
public class Day_{{DAY}}_{{YEAR}} extends Day {

    public Day_{{DAY}}_{{YEAR}}() {
        super({{YEAR}}, {{DAYNUM}});
    }

    @Override
    public String solvePart1() throws IOException {
        return Utils_Day{{DAY}}.solvePart1(year, dayNumber);
    }

    @Override
    public String solvePart2() throws IOException {
        return Utils_Day{{DAY}}.solvePart2(year, dayNumber);
    }
}
