package example.logic;

import java.util.List;

public class Xor implements Logic {

    List<Logic> ch;

    public Xor(Logic l, Logic r) {
        ch = List.of(l, r);
    }

    @Override
    public String toString() {
        return "Xor";
    }

    @Override
    public List<Logic> ch() {
        return ch;
    }
}
