package generator;

import lombok.SneakyThrows;
import org.antlr.v4.runtime.CharStreams;
import util.Pair;
import util.tokens.action.Action;
import util.tokens.node.Node;
import util.tokens.node.TypedNode;
import util.tokens.rule.Rule;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Base64;
import java.util.Comparator;
import java.util.Map;
import java.util.stream.Collectors;

public class ParserGenerator {
    @SneakyThrows
    public static void generate(String pack, String inputFile, String name) {
        Files.createDirectories(Path.of("src/main/java/" + pack.replaceAll("\\.","/")));

        TableGenerator.Result result = TableGenerator.generate(CharStreams.fromFileName(inputFile), name, pack);

        Map<Pair<Integer, Node>, Action> example = result.table;

        String serialize = serialize((Serializable) example);

        String functions = "public static List<Function<List<Object>, Object>> f = List.of(";
        int j = 0;
        for (Rule rule : result.rules.stream().sorted(Comparator.comparing(Rule::getInd)).collect(Collectors.toList())) {
            String format = String.format(functionPattern, rule.code);
            for (int i = 0; i < rule.right.size(); i++) {
                int ii = i;
                if (result.nodes.contains(rule.right.get(i))) {
                    TypedNode typedNode = result.nodes.stream().filter(n -> n.name.equals(rule.right.get(ii).name)).findAny().get();
                    format = format.replaceAll("\\$" + i, "((" + typedNode.type + ")l.get(" + i + "))");
                } else {
                    format = format.replaceAll("\\$" + i, "((" + "String" + ")l.get(" + i + "))");
                }

            }
            functions += format;
            if (j + 1 != result.rules.size()) {
                functions += ", \n";
            }
            j++;
        }
        functions += ");\n";

        String parser = String.format(pattern, pack, name, functions, serialize, result.nodes.stream().filter(s -> s.name.equals("start")).findAny().get().type,
                name, name,
                result.nodes.stream().filter(s -> s.name.equals("start")).findAny().get().type);

        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("src/main/java/" + pack.replaceAll("\\.", "/") + "/" + name + "Parser" + ".java"));
        bufferedWriter.write(parser);
        bufferedWriter.close();
    }


    @SneakyThrows
    private static String serialize(Serializable o) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        ObjectOutputStream oos = new ObjectOutputStream(baos);
        oos.writeObject(o);
        oos.close();
        return Base64.getEncoder().encodeToString(baos.toByteArray());
    }

    private static  final String functionPattern =
            "    l -> {\n" +
            "       return %s;\n" +
            "}\n";

    private static final String pattern =
            "package %s;\n" +
            "\n" +
            "import lombok.SneakyThrows;\n" +
            "import util.tokens.action.*;\n" +
            "import util.tokens.node.Node;\n" +
            "import util.tokens.node.Token;\n" +
            "import util.Pair;\n" +
            "import util.tokens.rule.Rule;\n" +
            "\n" +
            "import java.io.ByteArrayInputStream;\n" +
            "import java.io.ObjectInputStream;\n" +
            "import java.util.*;\n" +
            "import java.util.function.Function;\n" +
            "\n" +
            "public class %sParser {\n" +
            "    %s;\n" +
            "    public static String map = \"%s\";\n" +
            "\n" +
            "    @SneakyThrows\n" +
            "    private static Object deserialize(String s) {\n" +
            "        byte[] data = Base64.getDecoder().decode(s);\n" +
            "        ObjectInputStream ois = new ObjectInputStream(\n" +
            "                new ByteArrayInputStream(data));\n" +
            "        Object o = ois.readObject();\n" +
            "        ois.close();\n" +
            "        return o;\n" +
            "    }\n" +
            "\n" +
            "    public static Map<Pair<Integer, Node>, Action> table = ((Map<Pair<Integer, Node>, Action>) deserialize(map));\n" +
            "\n" +
            "    public static %s parse(String input) {\n" +
            "        %sLexer lexer = new %sLexer();\n\n" +
            "        Queue<Token> tokens = lexer.tokens(input);\n" +
            "        Deque<Integer> state = new ArrayDeque<>();\n" +
            "        Deque<Object> stack = new ArrayDeque<>();\n\n" +
            "        state.addFirst(0);\n\n" +
            "        while (!(table.get(new Pair<>(state.peekFirst(), tokens.peek())) instanceof Accept)) {\n" +
            "            Action action = table.get(new Pair<>(state.peekFirst(), tokens.peek()));\n\n" +
            "            if (action == null)\n" +
            "                throw new UnsupportedOperationException();\n\n" +
            "            if (action instanceof Shift) {\n" +
            "                state.addFirst(((Shift) action).getTo());\n" +
            "                stack.addFirst(tokens.poll().value);\n" +
            "            } else if (action instanceof Reduce) {\n" +
            "                Reduce reduce = (Reduce) action;\n" +
            "                List<Object> arg = new ArrayList<>();\n\n" +
            "                for (int i = 0; i < reduce.getRule().right.size(); i++) {\n" +
            "                    arg.add(stack.pollFirst());\n" +
            "                    state.removeFirst();\n" +
            "                }\n\n" +
            "                Collections.reverse(arg);\n" +
            "                Rule rule = reduce.getRule();\n" +
            "                int ind = rule.ind;\n" +
            "                state.addFirst(((GoTo) table.get(new Pair<>(state.peekFirst(), rule.left))).getTo());\n" +
            "                stack.addFirst(f.get(ind).apply(arg));\n" +
            "            }\n" +
            "        }\n\n" +
            "    return (%s)stack.pollFirst();\n" +
            "    }\n" +
            "}\n";
}
