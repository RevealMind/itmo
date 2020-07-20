package exception;

public class ParserException extends Exception {
    public ParserException(String errorMessage) {
        super(errorMessage);
    }

    public ParserException(String errorMessage, int ind) {
        super(String.format("%s at position %d", errorMessage, ind + 1));
    }
}
