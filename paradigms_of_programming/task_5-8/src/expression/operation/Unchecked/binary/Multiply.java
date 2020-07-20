package expression.operation.Unchecked.binary;

import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class Multiply extends BinaryOperation {
    public Multiply(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    protected int operation(int lValue, int rValue) {
        return lValue * rValue;
    }

    protected double operation(double lValue, double rValue) {
        return lValue * rValue;
    }
}
