package util.tokens.action;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class GoTo implements Action {
    public int to;
}
