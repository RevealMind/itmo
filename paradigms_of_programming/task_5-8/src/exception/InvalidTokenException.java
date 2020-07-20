package exception;

public class InvalidTokenException extends ParserException{
    public InvalidTokenException(String errorMessage, int ind) {
        super(String.format("unknown token %s at position %d", errorMessage, ind + 1));
    }

    public InvalidTokenException(char errorMessage, int ind) {
        super(String.format("unknown token %s at position %d", errorMessage, ind + 1));
    }
}
