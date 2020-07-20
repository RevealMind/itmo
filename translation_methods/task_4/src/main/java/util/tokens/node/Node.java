package util.tokens.node;

import lombok.AllArgsConstructor;
import lombok.Data;

import java.io.Serializable;

@Data
@AllArgsConstructor
public class Node implements Serializable {
    public String name;

    @Override
    public String toString() {
        return name;
    }
}
