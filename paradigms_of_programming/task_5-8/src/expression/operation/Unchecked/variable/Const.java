package expression.operation.Unchecked.variable;

import expression.TripleExpression;

public class Const implements TripleExpression {
    private final Number value;

    public Const(int value) {
        this.value = value;
    }
    public Const(double value) {
        this.value = value;
    }

    public int evaluate(int x) {
        return value.intValue();
    }

    public double evaluate(double x) {
        return value.doubleValue();
    }

    public int evaluate(int x, int y, int z) {
        return  value.intValue();
    }
}
