package util.tokens.action;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class Shift implements Action {
    public int to;
}
