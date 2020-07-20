package util.tokens.rule;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.EqualsAndHashCode;
import util.tokens.node.Node;

import java.io.Serializable;
import java.util.List;

@Data
@AllArgsConstructor
public class Rule implements Serializable {
    public int ind;
    public Node left;
    public List<Node> right;
    @EqualsAndHashCode.Exclude
    public String type;
    @EqualsAndHashCode.Exclude
    public String code;

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(ind).append(". ").append(left).append(" : ");
        right.forEach(node -> sb.append(node).append(" "));
        return sb.toString();
    }
}
