package Parser;

import exception.ConstOverflowException;
import exception.ParserException;
import expression.*;
import Parser.Token.*;
import expression.operation.Checked.Binary.CheckedAdd;
import expression.operation.Checked.Binary.CheckedDivide;
import expression.operation.Checked.Binary.CheckedMultiply;
import expression.operation.Checked.Binary.CheckedSubtract;
import expression.operation.Checked.CheckedConst;
import expression.operation.Checked.Unary.CheckedLogarithm;
import expression.operation.Checked.Unary.CheckedNegative;
import expression.operation.Checked.Unary.CheckedPow;
import expression.operation.Unchecked.unary.Negative;
import expression.operation.Unchecked.binary.*;
import expression.operation.Unchecked.variable.Const;
import expression.operation.Unchecked.variable.Variable;


public class ExpressionParser implements Parser {
    private Tokenizer tokens;
    int lastLeftBrackets = -1;

    public TripleExpression parse(String expression) throws ParserException {
        tokens = new Tokenizer(expression);
        return expr(false);
    }

    private TripleExpression expr(boolean isInBrackets) throws ParserException {
        TripleExpression ans = or();
        if (tokens.hasNext()) {
            Token curToken = tokens.next();
            switch (curToken.getType()) {
                case END:
                    if(isInBrackets)
                        throw new ParserException("no closing parenthesis for opening parenthesis", lastLeftBrackets);
                    break;
                case LEFT_BR:
                    throw new ParserException("unexpected ( found", curToken.getIdx());
                case RIGHT_BR:
                    if(!isInBrackets) {
                        throw new ParserException("no opening parenthesis for closing parenthesis", curToken.getIdx());
                    }
                    break;
                    default:
                        throw new ParserException("incorrect expression");
            }
        }
        return ans;
    }

    private TripleExpression or() throws ParserException {
        TripleExpression ans = xor();
        while (tokens.hasNext()) {
            Token curOperator = tokens.next();
            switch (curOperator.getType()) {
                case OR:
                    ans = new Or(ans, xor());
                    break;
                default:
                    tokens.prev();
                    return ans;
            }
        }
        return ans;
    }

    private TripleExpression xor() throws ParserException {
        TripleExpression ans = and();
        while (tokens.hasNext()) {
            Token curOperator = tokens.next();
            switch (curOperator.getType()) {
                case XOR:
                    ans = new Xor(ans, and());
                    break;
                default:
                    tokens.prev();
                    return ans;
            }
        }
        return ans;
    }

    private TripleExpression and() throws ParserException {
        TripleExpression ans = add();
        while (tokens.hasNext()) {
            Token curOperator = tokens.next();
            switch (curOperator.getType()) {
                case AND:
                    ans = new And(ans, add());
                    break;
                default:
                    tokens.prev();
                    return ans;
            }
        }
        return ans;
    }

    private TripleExpression add() throws ParserException {
        TripleExpression ans = term();
        while (tokens.hasNext()) {
            Token curOperation = tokens.next();
            switch (curOperation.getType()) {
                case PLUS:
                    ans = new CheckedAdd(ans, term());
                    break;
                case MINUS:
                    ans = new CheckedSubtract(ans, term());
                    break;
                default:
                    tokens.prev();
                    return ans;
            }
        }
        return ans;
    }

    private TripleExpression term() throws ParserException {
        TripleExpression ans = prim();
        while (tokens.hasNext()) {
            Token curOperation = tokens.next();
            switch (curOperation.getType()) {
                case MUL:
                    ans = new CheckedMultiply(ans, prim());
                    break;
                case DIV:
                    ans = new CheckedDivide(ans, prim());
                    break;
                default:
                    tokens.prev();
                    return ans;
            }
        }
        return ans;
    }

    private TripleExpression prim() throws ParserException {
        TripleExpression ans;
        Token token = tokens.next();
        switch (token.getType()) {
            case END:
            case RIGHT_BR:
                if (tokens.isFirst()) {
                    throw new ParserException("no opening parenthesis for closing parenthesis", token.getIdx());
                }
                Token _prev = tokens.prev();
                if (_prev.getType() == TokenType.LEFT_BR){
                    if (token.getType() == TokenType.RIGHT_BR) {
                        throw new ParserException(String.format("empty parenthesis sequence from %d to %d", _prev.getIdx() + 1, token.getIdx() + 1));
                    }
                }
                throw new ParserException(String.format("no last argument for operation %s", _prev.getValue()), _prev.getIdx());
            case CONST:
                ans = CheckedConst.valueOf(token.getValue(), token.getIdx());
                break;
            case VARIABLE:
                ans = new Variable(token.getValue());
                break;
            case MINUS:
                if (tokens.hasNext() && tokens.next().getType() == TokenType.CONST) {
                    Token number = tokens.cur();
                    ans = CheckedConst.valueOf("-" + number.getValue(), token.getIdx());
                } else {
                    tokens.prev();
                    ans = new CheckedNegative(prim());
                }
                break;
            case LEFT_BR:
                ans = expr(true);
                return ans;
            case LOG10:
                ans = new CheckedLogarithm(prim());
                break;
            case POW10:
                ans = new CheckedPow(prim());
                break;
            default:
                Token prev = tokens.prev();
                if (token.getIdx() == 0 || prev.getType() == TokenType.LEFT_BR || prev.getType() == TokenType.MINUS)
                    throw new ParserException(String.format("no first argument for oerator %s", token.getValue(), token.getIdx()));
                throw new ParserException(String.format("no middle argument between operator %s at position %d and operator %s",
                        prev.getValue(), prev.getIdx() + 1, token.getValue()),token.getIdx());
        }
        return ans;
    }


}
