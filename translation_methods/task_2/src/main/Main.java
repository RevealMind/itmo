package main;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Введи логическое выражение на языке Pascal");
        String input = in.nextLine();
        try {
            Parser parser = new Parser();
            Tree curTree = parser.parse(input);
            Visualizer treeVisualizer = new Visualizer();
            treeVisualizer.printToFile(input, curTree);
        } catch (ParserException e) {
            System.err.println(e.getMessage());
        }
    }
}
