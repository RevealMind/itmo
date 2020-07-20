package example.logic;

import java.util.List;

public class And implements Logic {

    List<Logic> ch;

    public And(Logic l, Logic r) {
        ch = List.of(l, r);
    }

    @Override
    public String toString() {
        return "And";
    }

    @Override
    public List<Logic> ch() {
        return ch;
    }
}
