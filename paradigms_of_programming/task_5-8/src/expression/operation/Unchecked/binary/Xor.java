package expression.operation.Unchecked.binary;

import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class Xor extends BinaryOperation {
    public Xor(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) {
        return lValue ^ rValue;
    }
}
