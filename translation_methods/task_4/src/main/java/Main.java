import generator.ParserGenerator;
import util.grammar.GrammarParserParser;

public class Main {
    public static void main(String[] args) {
        ParserGenerator.generate("example.calc", "calc.txt", "Calc");
        ParserGenerator.generate("example.logic", "logic.txt", "Logic");
    }
}
