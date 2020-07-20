package main;

public class ParserException extends Exception {
    public ParserException(String message) {
        super(message);
    }

    public ParserException(String message, Exception cause) {
        super(message, cause);
    }
}
