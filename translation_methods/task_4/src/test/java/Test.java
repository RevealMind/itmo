import example.calc.CalcParser;
import example.logic.LogicParser;
import org.junit.Assert;

import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        while (true) {
            String num = in.nextLine();
            System.out.println(CalcParser.parse(num));
        }
    }


    @org.junit.Test
    public void t1() {
        Assert.assertEquals(1, (int) CalcParser.parse("1"));
        Assert.assertEquals(1000_000, (int)CalcParser.parse("1000000"));
        Assert.assertEquals(120, (int)CalcParser.parse("1 * 2 * 3 * 4 * 5"));
        Assert.assertEquals(-120, (int)CalcParser.parse("1 * 2 * 3 * 4 * 5 - 1 * 2 * 3 * 4 * 5 - 1 * 2 * 3 * 4 * 5"));
        Assert.assertEquals(0, (int)CalcParser.parse("1 * 2 * 3 * 4 * 5 - 1 * 2 * 3 * 4 * 5 + 1 * 2 * 3 * 4 * 5 - 1 * 2 * 3 * 4 * 5"));
        Assert.assertEquals(1, (int)CalcParser.parse("(1)"));
        Assert.assertEquals(1, (int)CalcParser.parse("((((((1))))))"));
        Assert.assertEquals(200, (int)CalcParser.parse("(0 - 100)*(1 - 3)"));
        Assert.assertEquals(-200, (int)CalcParser.parse("(0 - 100)*(3 - 1)"));
        Assert.assertEquals(-13, (int)CalcParser.parse("1 - 2 - 3 - 4 - 5"));
        Assert.assertEquals(-21, (int)CalcParser.parse("1 - 2 - 3 * 2 - 4 - 5 * 2"));
        Assert.assertEquals(-23, (int)CalcParser.parse("(12 - 5) * 3 + 24 - 4 * (6 + 11)"));
    }

    @org.junit.Test
    public void t2() {
        TreeVisualizator.show(LogicParser.parse("(a and b) or not (c xor (a or not b))"));
        TreeVisualizator.show(LogicParser.parse("a or b or c or d"));
        TreeVisualizator.show(LogicParser.parse("a or b xor c or d"));
        TreeVisualizator.show(LogicParser.parse("a or b or c and d"));
    }
}
