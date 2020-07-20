package expression.operation.Unchecked.binary;

import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class Add extends BinaryOperation {

    public Add(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    protected int operation(int lValue, int rValue) {
        return lValue + rValue;
    }
}
