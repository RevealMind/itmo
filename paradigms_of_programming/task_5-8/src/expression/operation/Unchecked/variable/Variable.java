package expression.operation.Unchecked.variable;

import expression.TripleExpression;

public class Variable implements TripleExpression {
    private final String variable;

    public Variable(String variable) {
        this.variable = variable;
    }

    public int evaluate(int x) {
        return x;
    }

    public double evaluate(double x) {
        return x;
    }

    public int evaluate(int x, int y, int z) {
        switch (variable) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
        }
        return 0;
    }
}
