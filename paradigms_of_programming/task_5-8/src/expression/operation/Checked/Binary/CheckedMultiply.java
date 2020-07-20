package expression.operation.Checked.Binary;

import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class CheckedMultiply extends BinaryOperation{
    public CheckedMultiply(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) {
        if (lValue > 0 && rValue > 0 && lValue > Integer.MAX_VALUE / rValue ||
            lValue > 0 && rValue < 0 && rValue < Integer.MIN_VALUE / lValue ||
            lValue < 0 && rValue > 0 && lValue < Integer.MIN_VALUE / rValue||
            lValue < 0 && rValue < 0 && lValue < Integer.MAX_VALUE / rValue)
            throw new OverflowException(lValue, "*", rValue);
        return lValue * rValue;
    }
}
