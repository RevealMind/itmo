package util.tokens.action;

import lombok.AllArgsConstructor;
import lombok.Data;
import util.tokens.rule.Rule;

@Data
@AllArgsConstructor
public class Reduce implements Action {
    public String code;
    public Rule rule;
}
