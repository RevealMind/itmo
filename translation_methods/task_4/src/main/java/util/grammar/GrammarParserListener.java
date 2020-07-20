// Generated from D:/Projects/MT/LALR/src/main/java/util/grammar\GrammarParser.g4 by ANTLR 4.7.2
package util.grammar;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GrammarParserParser}.
 */
public interface GrammarParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(GrammarParserParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(GrammarParserParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#file}.
	 * @param ctx the parse tree
	 */
	void enterFile(GrammarParserParser.FileContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#file}.
	 * @param ctx the parse tree
	 */
	void exitFile(GrammarParserParser.FileContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#terminals}.
	 * @param ctx the parse tree
	 */
	void enterTerminals(GrammarParserParser.TerminalsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#terminals}.
	 * @param ctx the parse tree
	 */
	void exitTerminals(GrammarParserParser.TerminalsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#terminal}.
	 * @param ctx the parse tree
	 */
	void enterTerminal(GrammarParserParser.TerminalContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#terminal}.
	 * @param ctx the parse tree
	 */
	void exitTerminal(GrammarParserParser.TerminalContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#nonterminals}.
	 * @param ctx the parse tree
	 */
	void enterNonterminals(GrammarParserParser.NonterminalsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#nonterminals}.
	 * @param ctx the parse tree
	 */
	void exitNonterminals(GrammarParserParser.NonterminalsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#first}.
	 * @param ctx the parse tree
	 */
	void enterFirst(GrammarParserParser.FirstContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#first}.
	 * @param ctx the parse tree
	 */
	void exitFirst(GrammarParserParser.FirstContext ctx);
	/**
	 * Enter a parse tree produced by {@link GrammarParserParser#nonterminal}.
	 * @param ctx the parse tree
	 */
	void enterNonterminal(GrammarParserParser.NonterminalContext ctx);
	/**
	 * Exit a parse tree produced by {@link GrammarParserParser#nonterminal}.
	 * @param ctx the parse tree
	 */
	void exitNonterminal(GrammarParserParser.NonterminalContext ctx);
}