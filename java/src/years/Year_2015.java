package years;

import core.Calendar;
import year_2015.*;

public class Year_2015 extends Calendar {

    public Year_2015() {
        super(2015);
    }

    @Override
    protected void inicializeDays() {
        addDay(1, new Day_01_2015());
        addDay(2, new Day_02_2015());
        addDay(3, new Day_03_2015());
        addDay(4, new Day_04_2015());
        addDay(5, new Day_05_2015());
        addDay(6, new Day_06_2015());
        addDay(7, new Day_07_2015());
        addDay(8, new Day_08_2015());
        addDay(9, new Day_09_2015());
        addDay(10, new Day_10_2015());
        addDay(11, new Day_11_2015());
        addDay(12, new Day_12_2015());
        addDay(13, new Day_13_2015());
        addDay(14, new Day_14_2015());
        addDay(15, new Day_15_2015());
        addDay(16, new Day_16_2015());
        addDay(17, new Day_17_2015());
        addDay(18, new Day_18_2015());
        addDay(19, new Day_19_2015());
        addDay(20, new Day_20_2015());
        addDay(21, new Day_21_2015());
        addDay(22, new Day_22_2015());
        addDay(23, new Day_23_2015());
        addDay(24, new Day_24_2015());
        addDay(25, new Day_25_2015());
    }

}
