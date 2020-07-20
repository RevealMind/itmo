package expression.operation;

import expression.TripleExpression;

public abstract class BinaryOperation implements TripleExpression {
    private final TripleExpression lValue;
    private final TripleExpression rValue;

    abstract protected int operation(int lValue, int rValue);

    public BinaryOperation(TripleExpression lValue, TripleExpression rValue) {
        this.lValue = lValue;
        this.rValue = rValue;
    }

    public int evaluate(int x, int y, int z) {
        return operation(lValue.evaluate(x, y, z), rValue.evaluate(x, y, z));
    }
}
