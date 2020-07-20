// Generated from D:/Projects/MT/LALR/src/main/java/util/grammar\GrammarParser.g4 by ANTLR 4.7.2
package util.grammar;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class GrammarParserLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, TERM_NAME=4, NONTERM_NAME=5, STRING=6, CODE=7, 
		TYPE=8, REGEX=9, WS=10;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "TERM_NAME", "NONTERM_NAME", "STRING", "CODE", 
			"TYPE", "REGEX", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "':'", "';'", "'start'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, "TERM_NAME", "NONTERM_NAME", "STRING", "CODE", 
			"TYPE", "REGEX", "WS"
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


	public GrammarParserLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "GrammarParser.g4"; }

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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2\f\\\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\3\2\3\2\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\5\3\5\7\5$\n\5\f\5\16\5"+
		"\'\13\5\3\6\3\6\7\6+\n\6\f\6\16\6.\13\6\3\7\3\7\7\7\62\n\7\f\7\16\7\65"+
		"\13\7\3\7\3\7\3\b\3\b\7\b;\n\b\f\b\16\b>\13\b\3\b\3\b\3\t\3\t\7\tD\n\t"+
		"\f\t\16\tG\13\t\3\t\3\t\3\n\3\n\3\n\3\n\7\nO\n\n\f\n\16\nR\13\n\3\n\3"+
		"\n\3\13\6\13W\n\13\r\13\16\13X\3\13\3\13\5\63<E\2\f\3\3\5\4\7\5\t\6\13"+
		"\7\r\b\17\t\21\n\23\13\25\f\3\2\b\3\2C\\\4\2\62;C\\\3\2c|\4\2\62;c|\4"+
		"\2$$^^\5\2\13\f\17\17\"\"\2c\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3"+
		"\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2"+
		"\2\25\3\2\2\2\3\27\3\2\2\2\5\31\3\2\2\2\7\33\3\2\2\2\t!\3\2\2\2\13(\3"+
		"\2\2\2\r/\3\2\2\2\178\3\2\2\2\21A\3\2\2\2\23J\3\2\2\2\25V\3\2\2\2\27\30"+
		"\7<\2\2\30\4\3\2\2\2\31\32\7=\2\2\32\6\3\2\2\2\33\34\7u\2\2\34\35\7v\2"+
		"\2\35\36\7c\2\2\36\37\7t\2\2\37 \7v\2\2 \b\3\2\2\2!%\t\2\2\2\"$\t\3\2"+
		"\2#\"\3\2\2\2$\'\3\2\2\2%#\3\2\2\2%&\3\2\2\2&\n\3\2\2\2\'%\3\2\2\2(,\t"+
		"\4\2\2)+\t\5\2\2*)\3\2\2\2+.\3\2\2\2,*\3\2\2\2,-\3\2\2\2-\f\3\2\2\2.,"+
		"\3\2\2\2/\63\7)\2\2\60\62\13\2\2\2\61\60\3\2\2\2\62\65\3\2\2\2\63\64\3"+
		"\2\2\2\63\61\3\2\2\2\64\66\3\2\2\2\65\63\3\2\2\2\66\67\7)\2\2\67\16\3"+
		"\2\2\28<\7}\2\29;\13\2\2\2:9\3\2\2\2;>\3\2\2\2<=\3\2\2\2<:\3\2\2\2=?\3"+
		"\2\2\2><\3\2\2\2?@\7\177\2\2@\20\3\2\2\2AE\7]\2\2BD\13\2\2\2CB\3\2\2\2"+
		"DG\3\2\2\2EF\3\2\2\2EC\3\2\2\2FH\3\2\2\2GE\3\2\2\2HI\7_\2\2I\22\3\2\2"+
		"\2JP\7$\2\2KO\n\6\2\2LM\7^\2\2MO\t\6\2\2NK\3\2\2\2NL\3\2\2\2OR\3\2\2\2"+
		"PN\3\2\2\2PQ\3\2\2\2QS\3\2\2\2RP\3\2\2\2ST\7$\2\2T\24\3\2\2\2UW\t\7\2"+
		"\2VU\3\2\2\2WX\3\2\2\2XV\3\2\2\2XY\3\2\2\2YZ\3\2\2\2Z[\b\13\2\2[\26\3"+
		"\2\2\2\13\2%,\63<ENPX\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}