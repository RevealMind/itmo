package main;

public class Parser {
    private LexicalAnalyzer lexicalAnalyzer;

    private Tree S() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case NOT:
            case VAR:
            case LBRACKET:
                // S -> A S'
                Tree a = A();
                Tree sprime = Sprime();
                return new Tree("S", a, sprime);
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());
        }
    }

    private Tree Sprime() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case END:
            case RBRACKET:
                // S' -> eps
                return new Tree("S'", new Tree("ε"));
            case OR:
            case XOR:
                // S' -> or A S' | xor A S'
                lexicalAnalyzer.nextToken();
                Tree a = A();
                Tree sprime = Sprime();
                return new Tree("S'", new Tree(token.toString()), a, sprime);
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());

        }
    }

    private Tree A() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case NOT:
            case VAR:
            case LBRACKET:
                // A  -> B A'
                Tree b = B();
                Tree aprime = Aprime();
                return new Tree("A", b, aprime);
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());
        }
    }

    private Tree Aprime() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case XOR:
            case OR:
            case END:
            case RBRACKET:
                // A' -> eps
                return new Tree("A'", new Tree("ε"));
            case AND:
                // A' -> and B A'
                lexicalAnalyzer.nextToken();
                Tree b = B();
                Tree aprime = Aprime();
                return new Tree("A'", new Tree("and"), b, aprime);
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());
        }
    }

    private Tree B() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case NOT:
                // B  -> not B
                lexicalAnalyzer.nextToken();
                Tree b = B();
                return new Tree("B", new Tree("not"), b);
            case VAR:
            case LBRACKET:
                // B  -> D
                Tree d = D();
                return new Tree("B", d);
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());
        }
    }

    private Tree D() throws ParserException {
        Token token = lexicalAnalyzer.getCurToken();
        switch (token) {
            case LBRACKET:
                // D  -> ( S )
                lexicalAnalyzer.nextToken();
                Tree s = S();
                if (lexicalAnalyzer.getCurToken() != Token.RBRACKET) {
                    throw new ParserException("ERROR: Unexpected token [" + lexicalAnalyzer.getCurToken() + "] at position" + lexicalAnalyzer.getCurPos());
                }
                lexicalAnalyzer.nextToken();
                return new Tree("D", new Tree("("), s, new Tree(")"));
            case VAR:
                // D  -> var
                String curWord = lexicalAnalyzer.getCurWord();
                lexicalAnalyzer.nextToken();
                return new Tree("D", new Tree(curWord));
            default:
                throw new ParserException("ERROR: Unexpected token [" + token + "] at position" + lexicalAnalyzer.getCurPos());
        }
    }

    public Tree parse(String input) throws ParserException {
        lexicalAnalyzer = new LexicalAnalyzer(input);
        lexicalAnalyzer.nextToken();
        Tree root = S();
        if (lexicalAnalyzer.getCurToken() != Token.END) {
            throw new ParserException("ERROR: Unexpected token [" + lexicalAnalyzer.getCurToken() + "] at position" + lexicalAnalyzer.getCurPos());
        }
        return root;
    }
}
