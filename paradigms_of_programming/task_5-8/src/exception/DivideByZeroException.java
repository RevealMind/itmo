package exception;

public class DivideByZeroException extends ArithmeticException {
    public DivideByZeroException(int left) {
        super(String.format("division by zero %d / 0", left));
    }
}
