package util.tokens.rule;

import lombok.EqualsAndHashCode;
import util.tokens.node.Node;

import java.util.List;

@EqualsAndHashCode(callSuper = true)
public class ExtendedRule extends Rule {
    public int dotPos;

    public ExtendedRule(Rule rule) {
        super(rule.ind, rule.left, rule.right, rule.type, rule.code);
        this.dotPos = 0;
    }

    public ExtendedRule(Rule rule, int dotPos) {
        super(rule.ind, rule.left, rule.right, rule.type, rule.code);
        this.dotPos = dotPos;
    }
    
    public ExtendedRule(int ind, Node left, List<Node> right, String type, String code, int dotPos) {
        super(ind, left, right, type, code);
        this.dotPos = dotPos;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();

        sb.append(left).append(" : ");

        for (int i = 0;  i < right.size(); i++) {
            if (i == dotPos) {
                sb.append("• ");
            }
            sb.append(right.get(i)).append(" ");
        }

        if (dotPos == right.size()) {
            sb.append("•");
        }

        return sb.toString();
    }
}
