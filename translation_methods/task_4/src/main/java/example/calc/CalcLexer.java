package example.calc;
import util.tokens.node.Token;
import util.Pair;

import java.util.ArrayDeque;
import java.util.List;
import java.util.Queue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class CalcLexer {
    List<Pair<String, String>> terminals = List.of(
        new Pair<>("ADD", "\\+"),
        new Pair<>("SUB", "-"),
        new Pair<>("MUL", "\\*"),
        new Pair<>("LP", "\\("),
        new Pair<>("RP", "\\)"),
        new Pair<>("POW", "\\^"),
        new Pair<>("NUM", "[0-9]+")
    );

    public Queue<Token> tokens(String input) {
        Queue<Token> queue = new ArrayDeque<>();
        int pos = 0;

        while (input.length() != 0) {
            for (Pair<String, String> terminal : terminals) {
                Pattern pattern = Pattern.compile("^" + terminal.getSecond());
                Matcher matcher = pattern.matcher(input);
                if (matcher.find()) {
                    pos = matcher.end();
                    queue.add(new Token(terminal.getFirst(), matcher.group()));
                    break;
                }
            }
            if (pos == 0) {
                throw new IllegalArgumentException("Doesn't match grammar");
            } else {
                input = input.substring(pos).strip();
            }
            pos = 0;
        }
        queue.add(new Token("END", ""));
        return queue;
    }
}
