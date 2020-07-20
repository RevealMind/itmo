package util.tokens.node;

import lombok.EqualsAndHashCode;

public class TypedNode extends Node {
    public String value;
    public String type;

    public TypedNode(String name, String value, String type) {
        super(name);
        this.value = value;
        this.type = type;
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
