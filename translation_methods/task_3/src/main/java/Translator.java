package main.java;

import main.antlr.ProgramParser;

import java.util.List;

public class Translator {
    private StringBuilder writer = new StringBuilder();

    private int tabs = 0;

    public String getWriter() {
        return writer.toString();
    }

    public void translate(ProgramParser parser) {
        buildMain(parser.start());
    }

    private void buildMain(ProgramParser.StartContext ctx) {
        writeTabs();
        writer.append("public class Main {\n");
        tabs++;

        writeTabs();
        writer.append("public static void main(String[] args) {\n");

        ProgramParser.ExpressionContext expressions = ctx.expression();
        tabs++;
        buildExpression(expressions);

        tabs--;
        writeTabs();
        writer.append("}\n");

        tabs--;
        writeTabs();
        writer.append("}");
    }

    private void buildExpression(ProgramParser.ExpressionContext ctx) {
        if (ctx.PRINT() != null) {
            writeTabs();
            writer.append("System.out.println(");
            buildArg(ctx.arg());
            writer.append(");\n");
        } else if (ctx.ASGN() != null) {
            writeTabs();
            writer.append(ctx.VAR().getText());

            writer.append(" = ");

            buildArg(ctx.arg());
            writer.append(";\n");
        } else if (ctx.IF() != null) {
            writeTabs();
            writer.append("if (");
            builCondition(ctx.condition(), true);
            writer.append(") {\n");
            tabs++;

            buildExpression(ctx.expression(0));
            tabs--;
            writeTabs();
            writer.append("}");
            if (ctx.elseif() != null) {
                buildElseIf(ctx.elseif());
            }
            if (ctx.expression(1) != null) {
                writer.append(" else {\n");
                tabs++;
                buildExpression(ctx.expression(1));
                tabs--;
                writeTabs();
                writer.append("}");
            }
            writer.append("\n");
        }
    }

    private void buildElseIf(ProgramParser.ElseifContext ctx) {
        writer.append(" else if (");
        builCondition(ctx.condition(), true);
        tabs++;

        writer.append(") {\n");

        buildExpression(ctx.expression());

        tabs--;
        writeTabs();
        writer.append("}");

        if (ctx.elseif() != null) {
            buildElseIf(ctx.elseif());
        }
    }

    private void buildArg(ProgramParser.ArgContext ctx) {
        if (ctx.condition() != null) {
            builCondition(ctx.condition(), true);
        } else if (ctx.number() != null) {
            buildNumber(ctx.number(), true);
        }
    }

    private void builCondition(ProgramParser.ConditionContext ctx, boolean isFirst) {
        if (ctx.VAR() != null) {
            writer.append(ctx.VAR().getText());
        } else if (ctx.BOOL_CONST() != null) {
            writer.append(ctx.BOOL_CONST().getText());
        } else if (ctx.BINARY_BOOL_OP() != null) {
            if (!isFirst)
                writer.append("(");
            builCondition(ctx.condition(0), false);
            writer.append(" ").append(ctx.BINARY_BOOL_OP().getText()).append(" ");
            builCondition(ctx.condition(1), false);
            if (!isFirst)
                writer.append(")");
        } else if (ctx.NOT() != null) {
            writer.append("!");
            builCondition(ctx.condition(0), false);
        } else if (ctx.CMP_OP() != null) {
            if (!isFirst)
                writer.append("(");
            buildNumber(ctx.number(0), false);
            writer.append(" ").append(ctx.CMP_OP().getText()).append(" ");
            buildNumber(ctx.number(1), false);
            if (!isFirst)
                writer.append(")");
        }
    }

    private void buildNumber(ProgramParser.NumberContext ctx, boolean isFirst) {
        if (ctx.NUM() != null) {
            writer.append(ctx.NUM().getText());
        } else if (ctx.VAR() != null) {
            writer.append(ctx.VAR().getText());
        } else if (ctx.BINARY_OP() != null) {
            if (!isFirst)
                writer.append("(");
            buildNumber(ctx.number(0), false);
            writer.append(" ").append(ctx.BINARY_OP().getText()).append(" ");
            buildNumber(ctx.number(1), false);
            if (!isFirst)
                writer.append(")");
        }
    }

    private void writeTabs() {
        writer.append("\t".repeat(tabs));
    }
}

