package util;

import lombok.EqualsAndHashCode;
import lombok.Value;

import java.io.Serializable;

@Value
@EqualsAndHashCode
public class Pair<T, S> implements Serializable {
    T first;
    S second;
}
