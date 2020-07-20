package expression.operation.Checked;

import exception.ConstOverflowException;
import expression.operation.Unchecked.variable.Const;

public class CheckedConst {
    public static Const valueOf(String value, int ind) throws ConstOverflowException {
        try {
            int number = Integer.parseInt(value);
            return new Const(number);
        } catch (NumberFormatException e) {
            throw new ConstOverflowException(value, ind);
        }
    }
}
