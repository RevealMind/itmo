package exception;

public class OverflowException extends ArithmeticException {
    public OverflowException(int leftArg, String operation, int rightArg) {
        super(String.format("overflow %d %s %d", leftArg, operation, rightArg));
    }

    public OverflowException(int arg, String operation) {
        super(String.format("overflow %s%d", operation, arg));
    }
}
