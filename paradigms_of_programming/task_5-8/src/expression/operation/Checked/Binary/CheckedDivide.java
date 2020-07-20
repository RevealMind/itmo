package expression.operation.Checked.Binary;

import exception.DivideByZeroException;
import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.BinaryOperation;

public class CheckedDivide extends BinaryOperation {
    public CheckedDivide(TripleExpression lValue, TripleExpression rValue) {
        super(lValue, rValue);
    }

    @Override
    protected int operation(int lValue, int rValue) throws ArithmeticException {
        if (rValue == 0) {
            throw new DivideByZeroException(lValue);
        }

        if (lValue == Integer.MIN_VALUE && rValue == -1) {
            throw new OverflowException(lValue, "/", rValue);
        }

        return lValue / rValue;
    }
}
