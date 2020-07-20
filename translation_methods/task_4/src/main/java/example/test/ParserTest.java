package example.test;

import lombok.SneakyThrows;
import util.tokens.action.*;
import util.tokens.node.Node;
import util.tokens.node.TypedNode;
import util.Pair;
import util.tokens.rule.Rule;

import java.io.ByteArrayInputStream;
import java.io.ObjectInputStream;
import java.util.*;
import java.util.function.Function;

public class ParserTest {
    public static List<Function<List<Object>, Object>> f = List.of(    l -> {
       return  ((Integer)l.get(0)) ;
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
       return Integer.parseInt(((String)l.get(0)));
}
, 
    l -> {
       return ((Integer)l.get(1));
}
);
;
    public static String map = "rO0ABXNyABFqYXZhLnV0aWwuSGFzaE1hcAUH2sHDFmDRAwACRgAKbG9hZEZhY3RvckkACXRocmVzaG9sZHhwP0AAAAAAAGB3CAAAAIAAAAA+c3IACXV0aWwuUGFpckw3x1Hb3hoVAgACTAAFZmlyc3R0ABJMamF2YS9sYW5nL09iamVjdDtMAAZzZWNvbmRxAH4AA3hwc3IAEWphdmEubGFuZy5JbnRlZ2VyEuKgpPeBhzgCAAFJAAV2YWx1ZXhyABBqYXZhLmxhbmcuTnVtYmVyhqyVHQuU4IsCAAB4cAAAAAVzcgAVdXRpbC50b2tlbnMubm9kZS5Ob2RlPecX780/qy4CAAFMAARuYW1ldAASTGphdmEvbGFuZy9TdHJpbmc7eHB0AANudW1zcgAXdXRpbC50b2tlbnMuYWN0aW9uLkdvVG8bh/Pfsg23WQIAAUkAAnRveHAAAAACc3EAfgACc3EAfgAFAAAAC3NxAH4ACHQAA01VTHNyABl1dGlsLnRva2Vucy5hY3Rpb24uUmVkdWNlZFM7/E5BfhUCAAJMAARjb2RlcQB+AAlMAARydWxldAAXTHV0aWwvdG9rZW5zL3J1bGUvUnVsZTt4cHQAAiQxc3IAFXV0aWwudG9rZW5zLnJ1bGUuUnVsZc6euGbgIDmkAgAFSQADaW5kTAAEY29kZXEAfgAJTAAEbGVmdHQAF0x1dGlsL3Rva2Vucy9ub2RlL05vZGU7TAAFcmlnaHR0ABBMamF2YS91dGlsL0xpc3Q7TAAEdHlwZXEAfgAJeHAAAAAHcQB+ABVzcQB+AAh0AANudW1zcgATamF2YS51dGlsLkFycmF5TGlzdHiB0h2Zx2GdAwABSQAEc2l6ZXhwAAAAA3cEAAAAA3NxAH4ACHQAAkxQc3EAfgAIdAADc3Vtc3EAfgAIdAACUlB4dAAHSW50ZWdlcnNxAH4AAnNxAH4ABQAAAAJzcQB+AAh0AANFTkRzcQB+ABJ0AAIkMHNxAH4AFgAAAAVxAH4AKnNxAH4ACHQAA211bHNxAH4AHAAAAAF3BAAAAAFzcQB+AAh0AANudW14dAAHSW50ZWdlcnNxAH4AAnNxAH4ABQAAAANzcQB+AAh0AANBRERzcgAYdXRpbC50b2tlbnMuYWN0aW9uLlNoaWZ0Kw2twVlzT4sCAAFJAAJ0b3hwAAAAB3Nx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";

    @SneakyThrows
    private static Object deserialize(String s) {
        byte[] data = Base64.getDecoder().decode(s);
        ObjectInputStream ois = new ObjectInputStream(
                new ByteArrayInputStream(data));
        Object o = ois.readObject();
        ois.close();
        return o;
    }

    public static Map<Pair<Integer, Node>, Action> example = ((Map<Pair<Integer, Node>, Action>) deserialize(map));

    public static Integer parse(String input) {
        LexerTest lexer = new LexerTest();
        Queue<TypedNode> tokens = lexer.tokens(input);
        Deque<Integer> state = new ArrayDeque<>();
        Deque<Object> stack = new ArrayDeque<>();
        state.addFirst(0);
        while (!(example.get(new Pair<>(state.peekFirst(), tokens.peek())) instanceof Accept)) {
            Action action = example.get(new Pair<>(state.peekFirst(), tokens.peek()));
            if (action == null)
                throw new UnsupportedOperationException("Grammar possibly is not LALR(1)");
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
                state.addFirst(((GoTo) example.get(new Pair<>(state.peekFirst(), rule.left))).getTo());
                stack.addFirst(f.get(ind).apply(arg));

            }
        }
    return (Integer)stack.pollFirst();
    }
}
