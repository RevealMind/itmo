package expression.operation.Checked.Binary;

import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class CheckedAdd extends BinaryOperation {
    public CheckedAdd(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) throws ArithmeticException{
        if (lValue > Integer.MAX_VALUE - rValue && rValue > 0 || lValue < Integer.MIN_VALUE - rValue && rValue < 0)
            throw new OverflowException(lValue, "+", rValue);
        return lValue + rValue;
    }
}
