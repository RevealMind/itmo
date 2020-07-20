package main;

public enum  Token {
    AND, OR, XOR, NOT, VAR, END, LBRACKET, RBRACKET;

    @Override
    public String toString() {
        return this.name();
    }
}
