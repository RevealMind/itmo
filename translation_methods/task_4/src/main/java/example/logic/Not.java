package example.logic;

import java.util.List;

public class Not implements Logic {

    List<Logic> ch;

    public Not(Logic l) {
        ch = List.of(l);
    }

    @Override
    public String toString() {
        return "Not";
    }

    @Override
    public List<Logic> ch() {
        return ch;
    }
}
