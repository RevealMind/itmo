package main;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

public class LexicalAnalyzer {
    private InputStream is;
    private int curChar;
    private int curPos;
    private Token curToken;
    private String curWord;

    public LexicalAnalyzer(InputStream is) throws ParserException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    public LexicalAnalyzer(String expr) throws ParserException {
        this(new ByteArrayInputStream(expr.getBytes()));
    }

    private boolean isBlank(int c) {
        return c == ' ' || c == '\r' || c == '\n' || c == '\t';
    }

    private void nextChar() throws ParserException {
        curPos++;
        try {
            curChar = is.read();
        } catch (IOException e) {
            throw new ParserException("ERROR: Cannot read from file", e);
        }
    }

    private boolean tokenByWord(String word) {
        if (word.equals("and")) {
            curToken = Token.AND;
            return true;
        } else if (word.equals("xor")) {
            curToken = Token.XOR;
            return true;
        } else if (word.equals("or")) {
            curToken = Token.OR;
            return true;
        } else if (word.equals("not")) {
            curToken = Token.NOT;
            return true;
        } else if (word.length() == 1) {
            curToken = Token.VAR;
            return true;
        }
        return false;
    }

    public void nextToken() throws ParserException {
        while (isBlank(curChar)) {
            nextChar();
        }

        switch (curChar) {
            case '(':
                curToken = Token.LBRACKET;
                curWord = "(";
                nextChar();
                break;
            case ')':
                curToken = Token.RBRACKET;
                curWord = ")";
                nextChar();
                break;
            case -1:
                curToken = Token.END;
                break;
            default:
                if (Character.isLetter(curChar)) {
                    StringBuilder word = new StringBuilder();
                    while (Character.isLetter(curChar)) {
                        word.append((char) curChar);
                        nextChar();
                    }

                    if (tokenByWord(word.toString())) {
                        curWord = word.toString();
                    } else {
                        throw new ParserException("ERROR: Unexpected word [" + word.toString() + "]");
                    }
                } else {
                    throw new ParserException("ERROR: Unexpected symbol [" + (char) curChar + "] in position " + curPos);
                }
        }
    }

    public int getCurPos() {
        return curPos;
    }

    public Token getCurToken() {
        return curToken;
    }

    public String getCurWord() {
        return curWord;
    }
}
