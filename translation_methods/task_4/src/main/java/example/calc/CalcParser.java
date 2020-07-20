package example.calc;

import lombok.SneakyThrows;
import util.tokens.action.*;
import util.tokens.node.Node;
import util.tokens.node.Token;
import util.Pair;
import util.tokens.rule.Rule;

import java.io.ByteArrayInputStream;
import java.io.ObjectInputStream;
import java.util.*;
import java.util.function.Function;

public class CalcParser {
    public static List<Function<List<Object>, Object>> f = List.of(    l -> {
       return ((Integer)l.get(0));
}
, 
    l -> {
       return ((Integer)l.get(0));
}
, 
    l -> {
       return ((Integer)l.get(0)) + ((Integer)l.get(2));
}
, 
    l -> {
       return ((Integer)l.get(0)) - ((Integer)l.get(2));
}
, 
    l -> {
       return ((Integer)l.get(0)) * ((Integer)l.get(2));
}
, 
    l -> {
       return ((Integer)l.get(0));
}
, 
    l -> {
       return (int)Math.pow(((Integer)l.get(0)),((Integer)l.get(2)));
}
, 
    l -> {
       return ((Integer)l.get(0));
}
, 
    l -> {
       return -((Integer)l.get(1));
}
, 
    l -> {
       return Integer.parseInt(((String)l.get(0)));
}
, 
    l -> {
       return ((Integer)l.get(1));
}
);
;
    public static String map = "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AH4AiXNxAH4AGHEAfgCUcQB+AJVzcQB+AAJxAH4AnXEAfgCJc3EAfgAYcQB+AJ9xAH4AoHNxAH4AAnEAfgCAcQB+AC1zcQB+AAwAAAAEc3EAfgACcQB+AGlxAH4AEHNxAH4AGHEAfgBscQB+AG1zcQB+AAJxAH4A3nEAfgC2c3EAfgAYcQB+AOFxAH4A4nNxAH4AAnEAfgB2cQB+AEFzcQB+AEMAAAAFc3EAfgACcQB+AEZzcQB+AAh0AANQT1dzcQB+AEMAAAAKc3EAfgACcQB+AAdxAH4AfHNxAH4ADAAAAAlzcQB+AAJxAH4AgHEAfgBic3EAfgBDAAAAAXNxAH4AAnEAfgAVcQB+AF5zcQB+ABhxAH4AG3EAfgAfc3EAfgACcQB+AEZxAH4AXnNxAH4AGHEAfgBIcQB+AElzcQB+AAJxAH4AB3EAfgAtc3EAfgAMAAAABHNxAH4AAnEAfgCdcQB+ABBzcQB+ABhxAH4An3EAfgCgc3EAfgACcQB+AA9xAH4A9nNxAH4AQwAAAAxzcQB+AAJxAH4AknEAfgAQc3EAfgAYcQB+AJRxAH4AlXNxAH4AAnEAfgAxcQB+ABZzcQB+ABhxAH4AM3EAfgA0c3EAfgACcQB+ACxxAH4AQXNxAH4AQwAAAAVzcQB+AAJxAH4AB3EAfgBic3EAfgBDAAAAAXNxAH4AAnEAfgDecQB+AIxzcQB+AEMAAAAIc3EAfgACcQB+AMFxAH4AanNxAH4AGHEAfgDDcQB+AMRzcQB+AAJxAH4AgHEAfgB3c3EAfgBDAAAAB3NxAH4AAnEAfgC1cQB+AN9zcQB+ABhxAH4AuHEAfgC5c3EAfgACcQB+ADFxAH4AiXNxAH4AGHEAfgAzcQB+ADRzcQB+AAJxAH4A3nEAfgAQc3EAfgAYcQB+AOFxAH4A4nNxAH4AAnEAfgB2cQB+AC1zcQB+AAwAAAAEc3EAfgACcQB+AFFxAH4AanNxAH4AGHEAfgBVcQB+AFZzcQB+AAJxAH4AB3EAfgB3c3EAfgBDAAAAB3NxAH4AAnEAfgDRcQB+AApzcQB+AAwAAAADc3EAfgACcQB+AHtxAH4AQXNxAH4AQwAAAAVzcQB+AAJxAH4AwXEAfgBec3EAfgAYcQB+AMNxAH4AxHNxAH4AAnEAfgC1cQB+AF5zcQB+ABhxAH4AuHEAfgC5c3EAfgACcQB+AHZxAH4AYnNxAH4AQwAAAAF4";

    @SneakyThrows
    private static Object deserialize(String s) {
        byte[] data = Base64.getDecoder().decode(s);
        ObjectInputStream ois = new ObjectInputStream(
                new ByteArrayInputStream(data));
        Object o = ois.readObject();
        ois.close();
        return o;
    }

    public static Map<Pair<Integer, Node>, Action> table = ((Map<Pair<Integer, Node>, Action>) deserialize(map));

    public static Integer parse(String input) {
        CalcLexer lexer = new CalcLexer();

        Queue<Token> tokens = lexer.tokens(input);
        Deque<Integer> state = new ArrayDeque<>();
        Deque<Object> stack = new ArrayDeque<>();

        state.addFirst(0);

        while (!(table.get(new Pair<>(state.peekFirst(), tokens.peek())) instanceof Accept)) {
            Action action = table.get(new Pair<>(state.peekFirst(), tokens.peek()));

            if (action == null)
                throw new UnsupportedOperationException();

            if (action instanceof Shift) {
                state.addFirst(((Shift) action).getTo());
                stack.addFirst(tokens.poll().value);
            } else if (action instanceof Reduce) {
                Reduce reduce = (Reduce) action;
                List<Object> arg = new ArrayList<>();

                for (int i = 0; i < reduce.getRule().right.size(); i++) {
                    arg.add(stack.pollFirst());
                    state.removeFirst();
                }

                Collections.reverse(arg);
                Rule rule = reduce.getRule();
                int ind = rule.ind;
                state.addFirst(((GoTo) table.get(new Pair<>(state.peekFirst(), rule.left))).getTo());
                stack.addFirst(f.get(ind).apply(arg));
            }
        }

    return (Integer)stack.pollFirst();
    }
}
