package expression.operation.Checked.Binary;

import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class CheckedSubtract extends BinaryOperation {
    public CheckedSubtract(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) {
        if (lValue < Integer.MIN_VALUE + rValue && rValue > 0 || lValue > Integer.MAX_VALUE + rValue && rValue < 0)
            throw new OverflowException(lValue, "-", rValue);
        return lValue - rValue;
    }
}
