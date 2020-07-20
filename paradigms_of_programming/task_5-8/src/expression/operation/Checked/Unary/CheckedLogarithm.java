package expression.operation.Checked.Unary;

import expression.TripleExpression;
import expression.operation.UnaryOperation;

public class CheckedLogarithm extends UnaryOperation {
    public CheckedLogarithm(TripleExpression value) {
        super(value);
    }

    private void assertLogarithm(int x) {
        if (x <= 0) {
            throw new ArithmeticException("invalid operation with logarithm " + x +  " // 10");
        }
    }
    @Override
    protected int operation(int x) {
        assertLogarithm(x);
        int ans = 0;
        while (x >= 10) {
            x /= 10;
            ans++;
        }
        return ans;
    }
}
