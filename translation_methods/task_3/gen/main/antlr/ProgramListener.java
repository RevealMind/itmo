// Generated from D:/Projects/MT/lab2/src/main/antlr\Program.g4 by ANTLR 4.7.2
package main.antlr;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ProgramParser}.
 */
public interface ProgramListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ProgramParser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(ProgramParser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(ProgramParser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link ProgramParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(ProgramParser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(ProgramParser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link ProgramParser#elseif}.
	 * @param ctx the parse tree
	 */
	void enterElseif(ProgramParser.ElseifContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#elseif}.
	 * @param ctx the parse tree
	 */
	void exitElseif(ProgramParser.ElseifContext ctx);
	/**
	 * Enter a parse tree produced by {@link ProgramParser#arg}.
	 * @param ctx the parse tree
	 */
	void enterArg(ProgramParser.ArgContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#arg}.
	 * @param ctx the parse tree
	 */
	void exitArg(ProgramParser.ArgContext ctx);
	/**
	 * Enter a parse tree produced by {@link ProgramParser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(ProgramParser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(ProgramParser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link ProgramParser#number}.
	 * @param ctx the parse tree
	 */
	void enterNumber(ProgramParser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by {@link ProgramParser#number}.
	 * @param ctx the parse tree
	 */
	void exitNumber(ProgramParser.NumberContext ctx);
}