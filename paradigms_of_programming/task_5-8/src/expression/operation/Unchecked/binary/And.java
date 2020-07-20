package expression.operation.Unchecked.binary;

import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class And extends BinaryOperation{

    public And(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) {
        return lValue & rValue;
    }
}
