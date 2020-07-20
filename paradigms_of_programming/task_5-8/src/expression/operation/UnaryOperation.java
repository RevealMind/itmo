package expression.operation;

import expression.TripleExpression;

public abstract class UnaryOperation implements TripleExpression {
    private final TripleExpression value;

    protected abstract int operation(int x);

    public UnaryOperation(TripleExpression value) {
        this.value = value;
    }

    public int evaluate(int x, int y, int z) {
        return operation(value.evaluate(x, y, z));
    }
}
