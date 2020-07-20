// Generated from D:/Projects/MT/lab2/src/main/antlr\Program.g4 by ANTLR 4.7.2
package main.antlr;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ProgramLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		BINARY_OP=1, BOOL_CONST=2, BINARY_BOOL_OP=3, NOT=4, CMP_OP=5, ASGN=6, 
		IF=7, ELSEIF=8, PRINT=9, NUM=10, VAR=11, WS=12;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"BINARY_OP", "BOOL_CONST", "BINARY_BOOL_OP", "NOT", "CMP_OP", "ASGN", 
			"IF", "ELSEIF", "PRINT", "NUM", "VAR", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, null, "'!'", null, "'='", "'if'", "'elseif'", "'print'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "BINARY_OP", "BOOL_CONST", "BINARY_BOOL_OP", "NOT", "CMP_OP", "ASGN", 
			"IF", "ELSEIF", "PRINT", "NUM", "VAR", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public ProgramLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Program.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\16g\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\5\3\'"+
		"\n\3\3\4\3\4\3\4\3\4\3\4\5\4.\n\4\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6"+
		"\3\6\3\6\3\6\5\6<\n\6\3\7\3\7\3\b\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t"+
		"\3\n\3\n\3\n\3\n\3\n\3\n\3\13\3\13\5\13R\n\13\3\13\3\13\7\13V\n\13\f\13"+
		"\16\13Y\13\13\5\13[\n\13\3\f\3\f\7\f_\n\f\f\f\16\fb\13\f\3\r\3\r\3\r\3"+
		"\r\2\2\16\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\3\2"+
		"\7\5\2,-//\61\61\4\2>>@@\4\2C\\c|\6\2\62;C\\aac|\5\2\13\f\17\17\"\"\2"+
		"q\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2"+
		"\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2"+
		"\2\31\3\2\2\2\3\33\3\2\2\2\5&\3\2\2\2\7-\3\2\2\2\t/\3\2\2\2\13;\3\2\2"+
		"\2\r=\3\2\2\2\17?\3\2\2\2\21B\3\2\2\2\23I\3\2\2\2\25Z\3\2\2\2\27\\\3\2"+
		"\2\2\31c\3\2\2\2\33\34\t\2\2\2\34\4\3\2\2\2\35\36\7v\2\2\36\37\7t\2\2"+
		"\37 \7w\2\2 \'\7g\2\2!\"\7h\2\2\"#\7c\2\2#$\7n\2\2$%\7u\2\2%\'\7g\2\2"+
		"&\35\3\2\2\2&!\3\2\2\2\'\6\3\2\2\2()\7(\2\2).\7(\2\2*+\7~\2\2+.\7~\2\2"+
		",.\7`\2\2-(\3\2\2\2-*\3\2\2\2-,\3\2\2\2.\b\3\2\2\2/\60\7#\2\2\60\n\3\2"+
		"\2\2\61<\t\3\2\2\62\63\7>\2\2\63<\7?\2\2\64\65\7@\2\2\65<\7?\2\2\66\67"+
		"\7?\2\2\67<\7?\2\289\7#\2\29:\7?\2\2:<\7?\2\2;\61\3\2\2\2;\62\3\2\2\2"+
		";\64\3\2\2\2;\66\3\2\2\2;8\3\2\2\2<\f\3\2\2\2=>\7?\2\2>\16\3\2\2\2?@\7"+
		"k\2\2@A\7h\2\2A\20\3\2\2\2BC\7g\2\2CD\7n\2\2DE\7u\2\2EF\7g\2\2FG\7k\2"+
		"\2GH\7h\2\2H\22\3\2\2\2IJ\7r\2\2JK\7t\2\2KL\7k\2\2LM\7p\2\2MN\7v\2\2N"+
		"\24\3\2\2\2O[\7\62\2\2PR\7/\2\2QP\3\2\2\2QR\3\2\2\2RS\3\2\2\2SW\4\63;"+
		"\2TV\4\62;\2UT\3\2\2\2VY\3\2\2\2WU\3\2\2\2WX\3\2\2\2X[\3\2\2\2YW\3\2\2"+
		"\2ZO\3\2\2\2ZQ\3\2\2\2[\26\3\2\2\2\\`\t\4\2\2]_\t\5\2\2^]\3\2\2\2_b\3"+
		"\2\2\2`^\3\2\2\2`a\3\2\2\2a\30\3\2\2\2b`\3\2\2\2cd\t\6\2\2de\3\2\2\2e"+
		"f\b\r\2\2f\32\3\2\2\2\n\2&-;QWZ`\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}