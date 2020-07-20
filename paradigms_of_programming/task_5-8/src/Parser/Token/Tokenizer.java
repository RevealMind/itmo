package Parser.Token;

import Parser.Parser;
import exception.InvalidTokenException;
import exception.ParserException;

import java.util.ArrayList;
import java.util.List;

public class Tokenizer {
    private List<Token> tokens = new ArrayList<>();
    private String expression;
    private int curPos = -1;

    public Tokenizer(String expression) throws ParserException {
        this.expression = expression;
        tokenize(expression);
        tokens.add(new Token(TokenType.END, "end", expression.length()));
        if (tokens.size() == 1) {
            throw new ParserException("empty expression");
        }
    }

    public boolean hasNext() {
        return curPos < tokens.size() - 1;
    }

    public Token next() {
        return tokens.get(++curPos);
    }

    public Token prev() {
        return tokens.get(--curPos);
    }

    public Token cur() {
        return tokens.get(curPos);
    }

    public boolean isFirst() {
        return curPos == 0;
    }

    private void tokenize(String s) throws InvalidTokenException {
        for (int i = 0; i < s.length(); i++) {
            if (Character.isWhitespace(s.charAt(i))) {
                continue;
            }
            switch (s.charAt(i)) {
                case '|':
                    tokens.add(new Token(TokenType.OR, "|", i));
                    break;
                case '^':
                    tokens.add(new Token(TokenType.XOR, "^", i));
                    break;
                case '&':
                    tokens.add(new Token(TokenType.AND, "&", i));
                    break;
                case '+':
                    tokens.add(new Token(TokenType.PLUS, "+", i));
                    break;
                case '-':
                    tokens.add(new Token(TokenType.MINUS, "-", i));
                    break;
                case '*':
                    tokens.add(new Token(TokenType.MUL, "*", i));
                    break;
                case '/':
                    tokens.add(new Token(TokenType.DIV, "/", i));
                    break;
                case '(':
                    tokens.add(new Token(TokenType.LEFT_BR, "(", i));
                    break;
                case ')':
                    tokens.add(new Token(TokenType.RIGHT_BR, ")", i));
                    break;
                case 'l':
                    i = getLongToken("log10", TokenType.LOG10, i);
                    break;
                case 'p':
                    i = getLongToken("pow10", TokenType.POW10, i);
                    break;
                case 'x':
                case 'y':
                case 'z':
                    tokens.add(new Token(TokenType.VARIABLE, String.valueOf(s.charAt(i)), i));
                    break;
                default:
                    if (!Character.isDigit(s.charAt(i)))
                        throw new InvalidTokenException(s.charAt(i), i);
                    int j = i;
                    while (j < s.length() && Character.isDigit(s.charAt(j))) {
                        j++;
                    }
                    String number = s.substring(i, j);
                    tokens.add(new Token(TokenType.CONST, number, i));
                    i = j - 1;
            }
        }
    }

    public int getLongToken(String token, TokenType type, int i) throws InvalidTokenException {
        if (i + token.length() >= expression.length()) {
            throw new InvalidTokenException(expression.substring(i), i);
        }
//        String sss = expression.substring(i, i + token.length());
        if (expression.substring(i, i + token.length()).equals(token)) {
            int j = i + token.length();
            if (Character.isAlphabetic(expression.charAt(j))) {
                throw new InvalidTokenException(token + expression.charAt(j), i);
            }
            tokens.add(new Token(type, token, i));
            i += token.length() - 1;
            return i;
        } else {
            int j = i;
            while (j < expression.length() && !Character.isWhitespace(expression.charAt(j))) {
                j++;
            }
            throw new InvalidTokenException(expression.substring(i, j) + String.format(" expected %s", token), i);
        }
    }
}




