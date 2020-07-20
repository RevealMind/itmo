package Parser.Token;

public class Token {
    private TokenType type;
    private String value;
    private int idx;

    public Token(TokenType type, String value, int idx) {
        this.type = type;
        this.value = value;
        this.idx = idx;
    }

    public TokenType getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    public int getIdx() {
        return idx;
    }
}
