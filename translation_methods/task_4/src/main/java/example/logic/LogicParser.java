package example.logic;

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

public class LogicParser {
    public static List<Function<List<Object>, Object>> f = List.of(    l -> {
       return  ((Logic)l.get(0)) ;
}
, 
    l -> {
       return  new Or(((Logic)l.get(0)), ((Logic)l.get(2))) ;
}
, 
    l -> {
       return  new Xor(((Logic)l.get(0)), ((Logic)l.get(2))) ;
}
, 
    l -> {
       return  ((Logic)l.get(0)) ;
}
, 
    l -> {
       return  new And(((Logic)l.get(0)), ((Logic)l.get(2))) ;
}
, 
    l -> {
       return  ((Logic)l.get(0)) ;
}
, 
    l -> {
       return  new Var(((String)l.get(0))) ;
}
, 
    l -> {
       return  new Not(((Logic)l.get(1))) ;
}
, 
    l -> {
       return  ((Logic)l.get(1)) ;
}
);
;
    public static String map = "rO0ABXNyABFqYXZhLnV0aWwuSGFzaE1hcAUH2sHDFmDRAwACRgAKbG9hZEZhY3RvckkACXRocmVzaG9sZHhwP0AAAAAAAGB3CAAAAIAAAABMc3IACXV0aWwuUGFpckw3x1Hb3hoVAgACTAAFZmlyc3R0ABJMamF2YS9sYW5nL09iamVjdDtMAAZzZWNvbmRxAH4AA3hwc3IAEWphdmEubGFuZy5JbnRlZ2VyEuKgpPeBhzgCAAFJAAV2YWx1ZXhyABBqYXZhLmxhbmcuTnVtYmVyhqyVHQuU4IsCAAB4cAAAAAJzcgAVdXRpbC50b2tlbnMubm9kZS5Ob2RlPecX780/qy4CAAFMAARuYW1ldAASTGphdmEvbGFuZy9TdHJpbmc7eHB0AANBTkRzcgAYdXRpbC50b2tlbnMuYWN0aW9uLlNoaWZ0Kw2twVlzT4sCAAFJAAJ0b3hwAAAAC3NxAH4AAnNxAH4ABQAAAA9xAH4ACnNxAH4ADAAAAAtzcQB+AAJzcQB+AAUAAAAIc3EAfgAIdAADYW5kc3IAF3V0aWwudG9rZW5zLmFjdGlvbi5Hb1RvG4fz37INt1kCAAFJAAJ0b3hwAAAAD3NxAH4AAnNxAH4ABQAAAAVzcQB+AAh0AANWQVJzcQB+AAwAAAABc3EAfgACcQB+AAdzcQB+AAh0AANYT1JzcgAZdXRpbC50b2tlbnMuYWN0aW9uLlJlZHVjZWRTO/xOQX4VAgACTAAEY29kZXEAfgAJTAAEcnVsZXQAF0x1dGlsL3Rva2Vucy9ydWxlL1J1bGU7eHB0AAQgJDAgc3IAFXV0aWwudG9rZW5zLnJ1bGUuUnVsZc6euGbgIDmkAgAFSQADaW5kTAAEY29kZXEAfgAJTAAEbGVmdHQAF0x1dGlsL3Rva2Vucy9ub2RlL05vZGU7TAAFcmlnaHR0ABBMamF2YS91dGlsL0xpc3Q7TAAEdHlwZXEAfgAJeHAAAAADcQB+ACJzcQB+AAh0AAVsb2dpY3NyABNqYXZhLnV0aWwuQXJyYXlMaXN0eIHSHZnHYZ0DAAFJAARzaXpleHAAAAABdwQAAAABc3EAfgAIdAADYW5keHQABUxvZ2ljc3EAfgACcQB+AAdzcQB+AAh0AANFTkRzcQB+AB9xAH4AInEAfgAmc3EAfgACc3EAfgAFAAAACnNxAH4ACHQAAk9Sc3EAfgAMAAAACHNxAH4AAnNxAH4ABQAAAAtzcQB+AAh0AAN2YXJzcQB+ABUAAAAMc3EAfgACcQB+AA9xAH4AHXNxAH4AH3QAECBuZXcgT3IoJDAsICQyKSBzcQB+ACMAAAABcQB+AD5zcQB+AAh0AAVsb2dpY3NxAH4AKQAAAAN3BAAAAANzcQB+AAh0AAVsb2dpY3NxAH4ACHQAAk9Sc3EAfgAIdAADYW5keHQABUxvZ2ljc3EAfgACcQB+AA9xAH4AL3NxAH4AH3EAfgA+cQB+AD9zcQB+AAJzcQB+AAUAAAAAc3EAfgAIdAADTk9Uc3EAfgAMAAAABXNxAH4AAnEAfgAPc3EAfgAIdAACUlBzcQB+AB9xAH4APnEAfgA/c3EAfgACcQB+AAdxAH4AUnNxAH4AH3EAfgAicQB+ACZzcQB+AAJzcQB+AAUAAAANc3EAfgAIdAADQU5Ec3EAfgAfdAAEICQxIHNxAH4AIwAAAAhxAH4AXHNxAH4ACHQAA3ZhcnNxAH4AKQAAAAN3BAAAAANzcQB+AAh0AAJMUHNxAH4ACHQABWxvZ2ljc3EAfgAIcQB+AFN4dAAFTG9naWNzcQB+AAJzcQB+AAUAAAAGcQB+ABNzcQB+ABUAAAACc3EAfgACcQB+AFhxAH4AL3NxAH4AH3EAfgBccQB+AF1zcQB+AAJxAH4AWHNxAH4ACHEAfgAec3EAfgAfcQB+AFxxAH4AXXNxAH4AAnEAfgA4cQB+AE5zcQB+AAwAAAAFc3EAfgACcQB+AFhxAH4AUnNxAH4AH3EAfgBccQB+AF1zcQB+AAJxAH4ATXEAfgBAc3EAfgAVAAAABHNxAH4AAnNxAH4ABQAAAAdxAH4AOXNxAH4AFQAAAANzcQB+AAJzcQB+AAUAAAAJc3EAfgAIcQB+AFpzcQB+AB90AA0gbmV3IE5vdCgkMSkgc3EAfgAjAAAAB3EAfgB8c3EAfgAIdAADdmFyc3EAfgApAAAAAncEAAAAAnNxAH4ACHQAA05PVHNxAH4ACHQAA3Zhcnh0AAVMb2dpY3NxAH4AAnNxAH4ABQAAAARxAH4ANHNxAH4ADAAAAAhzcQB+AAJxAH4AGHEAfgA5c3EAfgAVAAAACXNxAH4AAnEAfgB5cQB+AB1zcQB+AB9xAH4AfHEAfgB9c3EAfgACcQB+AHlxAH4AL3NxAH4AH3EAfgB8cQB+AH1zcQB+AAJxAH4AdnEAfgBOc3EAfgAMAAAABXNxAH4AAnEAfgB5cQB+AFJzcQB+AB9xAH4AfHEAfgB9c3EAfgACcQB+AE1xAH4AE3NxAH4AFQAAAAJzcQB+AAJxAH4AD3NxAH4ACHEAfgBGc3EAfgAfcQB+AD5xAH4AP3NxAH4AAnEAfgAHcQB+AJZzcQB+AB9xAH4AInEAfgAmc3EAfgACcQB+ABhxAH4ATnNxAH4ADAAAAAVzcQB+AAJxAH4AEnNxAH4ACHQAAkxQc3EAfgAMAAAABnNxAH4AAnEAfgBocQB+AEBzcQB+ABUAAAAKc3EAfgACcQB+ABJxAH4AGXNxAH4ADAAAAAFzcQB+AAJxAH4AWHNxAH4ACHEAfgBGc3EAfgAfcQB+AFxxAH4AXXNxAH4AAnEAfgBocQB+AJ1zcQB+AAwAAAAGc3EAfgACcQB+AGhxAH4AGXNxAH4ADAAAAAFzcQB+AAJzcQB+AAUAAAADcQB+AHpzcQB+AB90AAQgJDAgc3EAfgAjAAAABXEAfgCuc3EAfgAIdAADYW5kc3EAfgApAAAAAXcEAAAAAXNxAH4ACHQAA3Zhcnh0AAVMb2dpY3NxAH4AAnEAfgCscQB+AB1zcQB+AB9xAH4ArnEAfgCvc3EAfgACcQB+AKxxAH4AL3NxAH4AH3EAfgCucQB+AK9zcQB+AAJxAH4ArHEAfgBSc3EAfgAfcQB+AK5xAH4Ar3NxAH4AAnNxAH4ABQAAAA5xAH4ACnNxAH4ADAAAAAtzcQB+AAJzcQB+AAUAAAABcQB+AHpzcQB+AB90AA0gbmV3IFZhcigkMCkgc3EAfgAjAAAABnEAfgDCcQB+ADlzcQB+ACkAAAABdwQAAAABc3EAfgAIdAADVkFSeHQABUxvZ2ljc3EAfgACcQB+AL1xAH4AHXNxAH4AH3QAESBuZXcgWG9yKCQwLCAkMikgc3EAfgAjAAAAAnEAfgDKc3EAfgAIdAAFbG9naWNzcQB+ACkAAAADdwQAAAADc3EAfgAIdAAFbG9naWNzcQB+AAhxAH4AHnNxAH4ACHQAA2FuZHh0AAVMb2dpY3NxAH4AAnEAfgC9cQB+AC9zcQB+AB9xAH4AynEAfgDLc3EAfgACcQB+AHZxAH4AE3NxAH4AFQAAAA5zcQB+AAJxAH4AeXEAfgClc3EAfgAfcQB+AHxxAH4AfXNxAH4AAnEAfgDAcQB+AB1zcQB+AB9xAH4AwnEAfgDDc3EAfgACcQB+AMBxAH4AL3NxAH4AH3EAfgDCcQB+AMNzcQB+AAJxAH4AvXEAfgBSc3EAfgAfcQB+AMpxAH4Ay3NxAH4AAnEAfgDAcQB+AFJzcQB+AB9xAH4AwnEAfgDDc3EAfgACc3EAfgAFAAAADHEAfgB6c3EAfgAfdAARIG5ldyBBbmQoJDAsICQyKSBzcQB+ACMAAAAEcQB+AOZxAH4AE3NxAH4AKQAAAAN3BAAAAANzcQB+AAh0AANhbmRzcQB+AAhxAH4AWnNxAH4ACHQAA3Zhcnh0AAVMb2dpY3NxAH4AAnEAfgAScQB+ADlzcQB+ABUAAAADc3EAfgACcQB+AORxAH4AHXNxAH4AH3EAfgDmcQB+AOdzcQB+AAJxAH4A5HEAfgAvc3EAfgAfcQB+AOZxAH4A53NxAH4AAnEAfgDkcQB+AFJzcQB+AB9xAH4A5nEAfgDnc3EAfgACcQB+AE1xAH4AnXNxAH4ADAAAAAZzcQB+AAJxAH4ATXEAfgAZc3EAfgAMAAAAAXNxAH4AAnEAfgAzc3EAfgAIdAADWE9Sc3EAfgAMAAAAB3NxAH4AAnEAfgBocQB+ADlzcQB+ABUAAAADc3EAfgACcQB+ABJxAH4ATnNxAH4ADAAAAAVzcQB+AAJxAH4AM3NxAH4ACHQAAlJQc3EAfgAMAAAADXNxAH4AAnEAfgA4cQB+AJ1zcQB+AAwAAAAGc3EAfgACcQB+ADhxAH4AGXNxAH4ADAAAAAFzcQB+AAJxAH4AaHEAfgBOc3EAfgAMAAAABXNxAH4AAnEAfgCscQB+AKVzcQB+AB9xAH4ArnEAfgCvc3EAfgACcQB+AL1xAH4AlnNxAH4AH3EAfgDKcQB+AMtzcQB+AAJxAH4AwHEAfgClc3EAfgAfcQB+AMJxAH4Aw3NxAH4AAnEAfgB2cQB+AJ1zcQB+AAwAAAAGc3EAfgACcQB+AHZxAH4AGXNxAH4ADAAAAAFzcQB+AAJxAH4ATXEAfgA5c3EAfgAVAAAAA3NxAH4AAnEAfgCHcQB+APxzcQB+AAwAAAAHc3EAfgACcQB+AIdxAH4AL3NyABl1dGlsLnRva2Vucy5hY3Rpb24uQWNjZXB0TH8BIjGOJzUCAAB4cHNxAH4AAnEAfgDkcQB+AKVzcQB+AB9xAH4A5nEAfgDnc3EAfgACcQB+ABhxAH4AnXNxAH4ADAAAAAZ4";

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

    public static Logic parse(String input) {
        LogicLexer lexer = new LogicLexer();

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

    return (Logic)stack.pollFirst();
    }
}
