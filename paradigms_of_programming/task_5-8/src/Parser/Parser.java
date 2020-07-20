package Parser;

import exception.ParserException;
import expression.*;

public interface Parser {
    TripleExpression parse(String expression) throws ParserException;
}
