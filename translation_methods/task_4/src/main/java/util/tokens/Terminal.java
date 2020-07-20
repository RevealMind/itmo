package util.tokens;

import lombok.EqualsAndHashCode;
import lombok.Value;

@Value
@EqualsAndHashCode
public class Terminal {
    String name;
    String value;

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(name).append(" : \'").append(value).append("\'");
        return sb.toString();
    }
}
