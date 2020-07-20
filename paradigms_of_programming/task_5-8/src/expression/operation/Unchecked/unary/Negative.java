package expression.operation.Unchecked.unary;

import expression.TripleExpression;
import expression.operation.UnaryOperation;

public class Negative extends UnaryOperation {

    public Negative(TripleExpression value) {
        super(value);
    }

    protected double operation(double x) {
        return -x;
    }

    protected int operation(int x) {
        return -x;
    }
}
