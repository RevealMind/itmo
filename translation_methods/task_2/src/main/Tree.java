package main;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Tree {
    private String node;
    private int id = -1;
    private List<Tree> children;

    public Tree (String node, Tree... children) {
        this.node = node;
        this.children = Arrays.asList(children);
    }

    public Tree(String node) {
        this.node = node;
        children = new ArrayList<>();
    }

    public String getNode() {
        return node;
    }

    public int getId() {
        return id;
    }

    public List<Tree> getChildren() {
        return children;
    }

    public void setId(int id) {
        this.id = id;
    }
}
