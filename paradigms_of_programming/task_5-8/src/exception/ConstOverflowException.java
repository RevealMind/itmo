package exception;

public class ConstOverflowException extends ParserException {
    public ConstOverflowException(String errorMessage, int ind) {
        super(String.format("constant overflow %s at position %d", errorMessage, ind + 1));
    }
}
