package example.logic;

import java.util.List;

public class Var implements Logic {
    String name;

    public Var(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public List<Logic> ch() {
        return List.of();
    }
}
