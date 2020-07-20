package main;

import java.io.IOException;
import java.io.PrintWriter;

public class Visualizer {
    private PrintWriter pw;
    private int k = 0;

    public void printToFile(String name, Tree root) {
        try {
            pw = new PrintWriter(System.getProperty("user.dir") + "/graph/" + name + ".dot");
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
        pw.write("digraph Tree {\n");
        showTree(root);
        pw.write("}");
        pw.close();
    }

    private String showTree(Tree tree) {
        if (tree.getChildren().size() > 0) {
            tree.setId(k++);
            pw.write(tree.getId() + " [label=\"" + tree.getNode() + "\"];\n");
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < tree.getChildren().size(); i++) {
                if (i != tree.getChildren().size() - 1) {
                    sb.append(showTree(tree.getChildren().get(i))).append(",");
                } else {
                    sb.append(showTree(tree.getChildren().get(i)));
                }
            }
            pw.write(tree.getId() + " -> {" + sb.toString() + "};\n");
            return String.valueOf(tree.getId());
        } else {
            tree.setId(k++);
            pw.write(tree.getId() + " [label=\"" + tree.getNode() + "\", color=red];\n");
            return String.valueOf(tree.getId());
        }
    }
}
