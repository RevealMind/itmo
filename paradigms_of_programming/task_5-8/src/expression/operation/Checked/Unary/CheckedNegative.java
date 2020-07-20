package expression.operation.Checked.Unary;

import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.UnaryOperation;

public class CheckedNegative extends UnaryOperation{
    public CheckedNegative(TripleExpression value) {
        super(value);
    }

    @Override
    protected int operation(int x) {
        if (x == Integer.MIN_VALUE)
            throw new OverflowException(x, "-");
        return -x;
    }
}
