// Generated from D:/Projects/MT/LALR/src/main/java/util/grammar\GrammarParser.g4 by ANTLR 4.7.2
package util.grammar;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class GrammarParserParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, TERM_NAME=4, NONTERM_NAME=5, STRING=6, CODE=7, 
		TYPE=8, REGEX=9, WS=10;
	public static final int
		RULE_start = 0, RULE_file = 1, RULE_terminals = 2, RULE_terminal = 3, 
		RULE_nonterminals = 4, RULE_first = 5, RULE_nonterminal = 6;
	private static String[] makeRuleNames() {
		return new String[] {
			"start", "file", "terminals", "terminal", "nonterminals", "first", "nonterminal"
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

	@Override
	public String getGrammarFileName() { return "GrammarParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public GrammarParserParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class StartContext extends ParserRuleContext {
		public FileContext file() {
			return getRuleContext(FileContext.class,0);
		}
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitStart(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(14);
			file();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FileContext extends ParserRuleContext {
		public TerminalsContext terminals() {
			return getRuleContext(TerminalsContext.class,0);
		}
		public NonterminalsContext nonterminals() {
			return getRuleContext(NonterminalsContext.class,0);
		}
		public FileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_file; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterFile(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitFile(this);
		}
	}

	public final FileContext file() throws RecognitionException {
		FileContext _localctx = new FileContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_file);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(16);
			terminals();
			setState(17);
			nonterminals();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TerminalsContext extends ParserRuleContext {
		public List<TerminalContext> terminal() {
			return getRuleContexts(TerminalContext.class);
		}
		public TerminalContext terminal(int i) {
			return getRuleContext(TerminalContext.class,i);
		}
		public TerminalsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_terminals; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterTerminals(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitTerminals(this);
		}
	}

	public final TerminalsContext terminals() throws RecognitionException {
		TerminalsContext _localctx = new TerminalsContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_terminals);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(22);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TERM_NAME) {
				{
				{
				setState(19);
				terminal();
				}
				}
				setState(24);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TerminalContext extends ParserRuleContext {
		public TerminalNode TERM_NAME() { return getToken(GrammarParserParser.TERM_NAME, 0); }
		public TerminalNode REGEX() { return getToken(GrammarParserParser.REGEX, 0); }
		public TerminalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_terminal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterTerminal(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitTerminal(this);
		}
	}

	public final TerminalContext terminal() throws RecognitionException {
		TerminalContext _localctx = new TerminalContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_terminal);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(25);
			match(TERM_NAME);
			setState(26);
			match(T__0);
			setState(27);
			match(REGEX);
			setState(28);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NonterminalsContext extends ParserRuleContext {
		public FirstContext first() {
			return getRuleContext(FirstContext.class,0);
		}
		public List<NonterminalContext> nonterminal() {
			return getRuleContexts(NonterminalContext.class);
		}
		public NonterminalContext nonterminal(int i) {
			return getRuleContext(NonterminalContext.class,i);
		}
		public NonterminalsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nonterminals; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterNonterminals(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitNonterminals(this);
		}
	}

	public final NonterminalsContext nonterminals() throws RecognitionException {
		NonterminalsContext _localctx = new NonterminalsContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_nonterminals);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(30);
			first();
			setState(34);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==NONTERM_NAME) {
				{
				{
				setState(31);
				nonterminal();
				}
				}
				setState(36);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FirstContext extends ParserRuleContext {
		public TerminalNode TYPE() { return getToken(GrammarParserParser.TYPE, 0); }
		public TerminalNode NONTERM_NAME() { return getToken(GrammarParserParser.NONTERM_NAME, 0); }
		public TerminalNode CODE() { return getToken(GrammarParserParser.CODE, 0); }
		public FirstContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_first; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterFirst(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitFirst(this);
		}
	}

	public final FirstContext first() throws RecognitionException {
		FirstContext _localctx = new FirstContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_first);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(37);
			match(T__2);
			setState(38);
			match(TYPE);
			setState(39);
			match(T__0);
			setState(40);
			match(NONTERM_NAME);
			setState(41);
			match(CODE);
			setState(42);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NonterminalContext extends ParserRuleContext {
		public List<TerminalNode> NONTERM_NAME() { return getTokens(GrammarParserParser.NONTERM_NAME); }
		public TerminalNode NONTERM_NAME(int i) {
			return getToken(GrammarParserParser.NONTERM_NAME, i);
		}
		public TerminalNode TYPE() { return getToken(GrammarParserParser.TYPE, 0); }
		public TerminalNode CODE() { return getToken(GrammarParserParser.CODE, 0); }
		public List<TerminalNode> TERM_NAME() { return getTokens(GrammarParserParser.TERM_NAME); }
		public TerminalNode TERM_NAME(int i) {
			return getToken(GrammarParserParser.TERM_NAME, i);
		}
		public NonterminalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nonterminal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).enterNonterminal(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof GrammarParserListener ) ((GrammarParserListener)listener).exitNonterminal(this);
		}
	}

	public final NonterminalContext nonterminal() throws RecognitionException {
		NonterminalContext _localctx = new NonterminalContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_nonterminal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(44);
			match(NONTERM_NAME);
			setState(45);
			match(TYPE);
			setState(46);
			match(T__0);
			setState(50);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==TERM_NAME || _la==NONTERM_NAME) {
				{
				{
				setState(47);
				_la = _input.LA(1);
				if ( !(_la==TERM_NAME || _la==NONTERM_NAME) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				}
				}
				setState(52);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(53);
			match(CODE);
			setState(54);
			match(T__1);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\f;\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\3\2\3\2\3\3\3\3\3\3\3\4\7\4"+
		"\27\n\4\f\4\16\4\32\13\4\3\5\3\5\3\5\3\5\3\5\3\6\3\6\7\6#\n\6\f\6\16\6"+
		"&\13\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b\7\b\63\n\b\f\b\16\b"+
		"\66\13\b\3\b\3\b\3\b\3\b\2\2\t\2\4\6\b\n\f\16\2\3\3\2\6\7\2\66\2\20\3"+
		"\2\2\2\4\22\3\2\2\2\6\30\3\2\2\2\b\33\3\2\2\2\n \3\2\2\2\f\'\3\2\2\2\16"+
		".\3\2\2\2\20\21\5\4\3\2\21\3\3\2\2\2\22\23\5\6\4\2\23\24\5\n\6\2\24\5"+
		"\3\2\2\2\25\27\5\b\5\2\26\25\3\2\2\2\27\32\3\2\2\2\30\26\3\2\2\2\30\31"+
		"\3\2\2\2\31\7\3\2\2\2\32\30\3\2\2\2\33\34\7\6\2\2\34\35\7\3\2\2\35\36"+
		"\7\13\2\2\36\37\7\4\2\2\37\t\3\2\2\2 $\5\f\7\2!#\5\16\b\2\"!\3\2\2\2#"+
		"&\3\2\2\2$\"\3\2\2\2$%\3\2\2\2%\13\3\2\2\2&$\3\2\2\2\'(\7\5\2\2()\7\n"+
		"\2\2)*\7\3\2\2*+\7\7\2\2+,\7\t\2\2,-\7\4\2\2-\r\3\2\2\2./\7\7\2\2/\60"+
		"\7\n\2\2\60\64\7\3\2\2\61\63\t\2\2\2\62\61\3\2\2\2\63\66\3\2\2\2\64\62"+
		"\3\2\2\2\64\65\3\2\2\2\65\67\3\2\2\2\66\64\3\2\2\2\678\7\t\2\289\7\4\2"+
		"\29\17\3\2\2\2\5\30$\64";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}