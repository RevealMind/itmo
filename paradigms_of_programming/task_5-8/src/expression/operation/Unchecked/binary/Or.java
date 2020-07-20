package expression.operation.Unchecked.binary;

import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class Or extends BinaryOperation{
    public Or(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) {
        return lValue | rValue;
    }
}
