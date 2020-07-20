package expression.operation.Checked.Unary;

import exception.OverflowException;
import expression.TripleExpression;
import expression.operation.UnaryOperation;

public class CheckedPow extends UnaryOperation {
    public CheckedPow(TripleExpression value) {
        super(value);
    }


    private int multiply(int lValue, int rValue) {
        if (lValue > 0 && rValue > 0 && lValue > Integer.MAX_VALUE / rValue ||
                lValue > 0 && rValue < 0 && rValue < Integer.MIN_VALUE / lValue ||
                lValue < 0 && rValue > 0 && lValue < Integer.MIN_VALUE / rValue ||
                lValue < 0 && rValue < 0 && lValue < Integer.MAX_VALUE / rValue)
            throw new OverflowException(lValue, "*", rValue);
        return lValue * rValue;
    }

    @Override
    protected int operation(int x) {
        if (x < 0) {
            throw new ArithmeticException("invalid pow ** " + x);
        }
        int ans = 1;
        int pow = 10;
        while (x != 0) {
            if (x % 2 != 0) {
                ans = multiply(ans, pow);
                if (x == 1)
                    break;
            }
            pow = multiply(pow, pow);
            x /= 2;
        }
        return ans;
    }
}
