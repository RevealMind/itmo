// Generated from D:/Projects/MT/lab2/src/main/antlr\Program.g4 by ANTLR 4.7.2
package main.antlr;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ProgramParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.7.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		BINARY_OP=1, BOOL_CONST=2, BINARY_BOOL_OP=3, NOT=4, CMP_OP=5, ASGN=6, 
		IF=7, ELSEIF=8, PRINT=9, NUM=10, VAR=11, WS=12;
	public static final int
		RULE_start = 0, RULE_expression = 1, RULE_elseif = 2, RULE_arg = 3, RULE_condition = 4, 
		RULE_number = 5;
	private static String[] makeRuleNames() {
		return new String[] {
			"start", "expression", "elseif", "arg", "condition", "number"
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

	@Override
	public String getGrammarFileName() { return "Program.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ProgramParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class StartContext extends ParserRuleContext {
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode EOF() { return getToken(ProgramParser.EOF, 0); }
		public StartContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_start; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterStart(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitStart(this);
		}
	}

	public final StartContext start() throws RecognitionException {
		StartContext _localctx = new StartContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_start);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(12);
			expression();
			setState(13);
			match(EOF);
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

	public static class ExpressionContext extends ParserRuleContext {
		public TerminalNode PRINT() { return getToken(ProgramParser.PRINT, 0); }
		public ArgContext arg() {
			return getRuleContext(ArgContext.class,0);
		}
		public TerminalNode ASGN() { return getToken(ProgramParser.ASGN, 0); }
		public TerminalNode VAR() { return getToken(ProgramParser.VAR, 0); }
		public TerminalNode IF() { return getToken(ProgramParser.IF, 0); }
		public ConditionContext condition() {
			return getRuleContext(ConditionContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ElseifContext elseif() {
			return getRuleContext(ElseifContext.class,0);
		}
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitExpression(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		ExpressionContext _localctx = new ExpressionContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_expression);
		try {
			setState(29);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case PRINT:
				enterOuterAlt(_localctx, 1);
				{
				setState(15);
				match(PRINT);
				setState(16);
				arg();
				}
				break;
			case ASGN:
				enterOuterAlt(_localctx, 2);
				{
				setState(17);
				match(ASGN);
				setState(18);
				match(VAR);
				setState(19);
				arg();
				}
				break;
			case IF:
				enterOuterAlt(_localctx, 3);
				{
				setState(20);
				match(IF);
				setState(21);
				condition();
				setState(22);
				expression();
				setState(24);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
				case 1:
					{
					setState(23);
					elseif();
					}
					break;
				}
				setState(27);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
				case 1:
					{
					setState(26);
					expression();
					}
					break;
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class ElseifContext extends ParserRuleContext {
		public TerminalNode ELSEIF() { return getToken(ProgramParser.ELSEIF, 0); }
		public ConditionContext condition() {
			return getRuleContext(ConditionContext.class,0);
		}
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public ElseifContext elseif() {
			return getRuleContext(ElseifContext.class,0);
		}
		public ElseifContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elseif; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterElseif(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitElseif(this);
		}
	}

	public final ElseifContext elseif() throws RecognitionException {
		ElseifContext _localctx = new ElseifContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_elseif);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(31);
			match(ELSEIF);
			setState(32);
			condition();
			setState(33);
			expression();
			setState(35);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				{
				setState(34);
				elseif();
				}
				break;
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

	public static class ArgContext extends ParserRuleContext {
		public ConditionContext condition() {
			return getRuleContext(ConditionContext.class,0);
		}
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public ArgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arg; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterArg(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitArg(this);
		}
	}

	public final ArgContext arg() throws RecognitionException {
		ArgContext _localctx = new ArgContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_arg);
		try {
			setState(39);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(37);
				condition();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(38);
				number();
				}
				break;
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

	public static class ConditionContext extends ParserRuleContext {
		public TerminalNode VAR() { return getToken(ProgramParser.VAR, 0); }
		public TerminalNode BOOL_CONST() { return getToken(ProgramParser.BOOL_CONST, 0); }
		public TerminalNode BINARY_BOOL_OP() { return getToken(ProgramParser.BINARY_BOOL_OP, 0); }
		public List<ConditionContext> condition() {
			return getRuleContexts(ConditionContext.class);
		}
		public ConditionContext condition(int i) {
			return getRuleContext(ConditionContext.class,i);
		}
		public TerminalNode NOT() { return getToken(ProgramParser.NOT, 0); }
		public TerminalNode CMP_OP() { return getToken(ProgramParser.CMP_OP, 0); }
		public List<NumberContext> number() {
			return getRuleContexts(NumberContext.class);
		}
		public NumberContext number(int i) {
			return getRuleContext(NumberContext.class,i);
		}
		public ConditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_condition; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterCondition(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitCondition(this);
		}
	}

	public final ConditionContext condition() throws RecognitionException {
		ConditionContext _localctx = new ConditionContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_condition);
		try {
			setState(53);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case VAR:
				enterOuterAlt(_localctx, 1);
				{
				setState(41);
				match(VAR);
				}
				break;
			case BOOL_CONST:
				enterOuterAlt(_localctx, 2);
				{
				setState(42);
				match(BOOL_CONST);
				}
				break;
			case BINARY_BOOL_OP:
				enterOuterAlt(_localctx, 3);
				{
				setState(43);
				match(BINARY_BOOL_OP);
				setState(44);
				condition();
				setState(45);
				condition();
				}
				break;
			case NOT:
				enterOuterAlt(_localctx, 4);
				{
				setState(47);
				match(NOT);
				setState(48);
				condition();
				}
				break;
			case CMP_OP:
				enterOuterAlt(_localctx, 5);
				{
				setState(49);
				match(CMP_OP);
				setState(50);
				number();
				setState(51);
				number();
				}
				break;
			default:
				throw new NoViableAltException(this);
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

	public static class NumberContext extends ParserRuleContext {
		public TerminalNode NUM() { return getToken(ProgramParser.NUM, 0); }
		public TerminalNode VAR() { return getToken(ProgramParser.VAR, 0); }
		public TerminalNode BINARY_OP() { return getToken(ProgramParser.BINARY_OP, 0); }
		public List<NumberContext> number() {
			return getRuleContexts(NumberContext.class);
		}
		public NumberContext number(int i) {
			return getRuleContext(NumberContext.class,i);
		}
		public NumberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).enterNumber(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof ProgramListener ) ((ProgramListener)listener).exitNumber(this);
		}
	}

	public final NumberContext number() throws RecognitionException {
		NumberContext _localctx = new NumberContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_number);
		try {
			setState(61);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case NUM:
				enterOuterAlt(_localctx, 1);
				{
				setState(55);
				match(NUM);
				}
				break;
			case VAR:
				enterOuterAlt(_localctx, 2);
				{
				setState(56);
				match(VAR);
				}
				break;
			case BINARY_OP:
				enterOuterAlt(_localctx, 3);
				{
				setState(57);
				match(BINARY_OP);
				setState(58);
				number();
				setState(59);
				number();
				}
				break;
			default:
				throw new NoViableAltException(this);
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
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3\16B\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\5\3\33\n\3\3\3\5\3\36\n\3\5\3 \n\3\3\4\3\4\3\4\3\4\5\4&\n"+
		"\4\3\5\3\5\5\5*\n\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\5"+
		"\68\n\6\3\7\3\7\3\7\3\7\3\7\3\7\5\7@\n\7\3\7\2\2\b\2\4\6\b\n\f\2\2\2G"+
		"\2\16\3\2\2\2\4\37\3\2\2\2\6!\3\2\2\2\b)\3\2\2\2\n\67\3\2\2\2\f?\3\2\2"+
		"\2\16\17\5\4\3\2\17\20\7\2\2\3\20\3\3\2\2\2\21\22\7\13\2\2\22 \5\b\5\2"+
		"\23\24\7\b\2\2\24\25\7\r\2\2\25 \5\b\5\2\26\27\7\t\2\2\27\30\5\n\6\2\30"+
		"\32\5\4\3\2\31\33\5\6\4\2\32\31\3\2\2\2\32\33\3\2\2\2\33\35\3\2\2\2\34"+
		"\36\5\4\3\2\35\34\3\2\2\2\35\36\3\2\2\2\36 \3\2\2\2\37\21\3\2\2\2\37\23"+
		"\3\2\2\2\37\26\3\2\2\2 \5\3\2\2\2!\"\7\n\2\2\"#\5\n\6\2#%\5\4\3\2$&\5"+
		"\6\4\2%$\3\2\2\2%&\3\2\2\2&\7\3\2\2\2\'*\5\n\6\2(*\5\f\7\2)\'\3\2\2\2"+
		")(\3\2\2\2*\t\3\2\2\2+8\7\r\2\2,8\7\4\2\2-.\7\5\2\2./\5\n\6\2/\60\5\n"+
		"\6\2\608\3\2\2\2\61\62\7\6\2\2\628\5\n\6\2\63\64\7\7\2\2\64\65\5\f\7\2"+
		"\65\66\5\f\7\2\668\3\2\2\2\67+\3\2\2\2\67,\3\2\2\2\67-\3\2\2\2\67\61\3"+
		"\2\2\2\67\63\3\2\2\28\13\3\2\2\29@\7\f\2\2:@\7\r\2\2;<\7\3\2\2<=\5\f\7"+
		"\2=>\5\f\7\2>@\3\2\2\2?9\3\2\2\2?:\3\2\2\2?;\3\2\2\2@\r\3\2\2\2\t\32\35"+
		"\37%)\67?";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}