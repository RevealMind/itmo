package generator;

import lombok.SneakyThrows;
import util.tokens.Terminal;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.List;

public class LexerGenerator {
    @SneakyThrows
    public static void generateLexer(String name, List<Terminal> terminals, String pack) {
        String file = String.format(pattern, pack, name, terms(terminals));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("src/main/java/" + pack.replaceAll("\\.", "/") + "/" + name + "Lexer" + ".java"));
        bufferedWriter.write(file);
        bufferedWriter.close();
    }

    private static String terms(List<Terminal> terminals) {
        StringBuilder res = new StringBuilder();
        String tab = "        ";
        if (terminals.size() > 0) {
            res.append(tab).append("new Pair<>(\"").append(terminals.get(0).getName()).append("\", \"").append(terminals.get(0).getValue()).append("\")");
        }
        for (int i = 1; i < terminals.size(); i++) {
            res.append(",\n").append(tab).append("new Pair<>(\"").append(terminals.get(i).getName()).append("\", \"").append(terminals.get(i).getValue()).append("\")");
        }
        return res.toString();
    }

    private static final String pattern =
        "package %s;\n" +
        "import util.tokens.node.Token;\n" +
        "import util.Pair;\n" +
        "\n" +
        "import java.util.ArrayDeque;\n" +
        "import java.util.List;\n" +
        "import java.util.Queue;\n" +
        "import java.util.regex.Matcher;\n" +
        "import java.util.regex.Pattern;\n" +
        "\n" +
        "public class %sLexer {\n" +
        "    List<Pair<String, String>> terminals = List.of(\n" +
        "%s\n" +
        "    );\n" +
        "\n" +
        "    public Queue<Token> tokens(String input) {\n" +
        "        Queue<Token> queue = new ArrayDeque<>();\n" +
        "        int pos = 0;\n" +
        "\n" +
        "        while (input.length() != 0) {\n" +
        "            for (Pair<String, String> terminal : terminals) {\n" +
        "                Pattern pattern = Pattern.compile(\"^\" + terminal.getSecond());\n" +
        "                Matcher matcher = pattern.matcher(input);\n" +
        "                if (matcher.find()) {\n" +
        "                    pos = matcher.end();\n" +
        "                    queue.add(new Token(terminal.getFirst(), matcher.group()));\n" +
        "                    break;\n" +
        "                }\n" +
        "            }\n" +
        "            if (pos == 0) {\n" +
        "                throw new IllegalArgumentException(\"Doesn't match grammar\");\n" +
        "            } else {\n" +
        "                input = input.substring(pos).strip();\n" +
        "            }\n" +
        "            pos = 0;\n" +
        "        }\n" +
        "        queue.add(new Token(\"END\", \"\"));\n" +
        "        return queue;\n" +
        "    }\n" +
        "}\n";
}
