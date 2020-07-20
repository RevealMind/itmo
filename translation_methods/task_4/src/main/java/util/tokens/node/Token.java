package util.tokens.node;


public class Token extends Node {
    public String value;

    public Token(String name, String value) {
        super(name);
        this.value = value;
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    @Override
    public boolean equals(Object o) {
        return super.equals(o);
    }
}
