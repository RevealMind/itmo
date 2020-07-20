package ru.ifmo.rain.janchenkov.arrayset;

import java.util.AbstractList;
import java.util.List;
import java.util.RandomAccess;

public class ReversedList<T> extends AbstractList<T> implements RandomAccess{
    private boolean isReversed;
    private final List<T> elements;

    public ReversedList(List<T> list) {
        elements = list;
        isReversed = false;
    }

    public void reverse() {
        isReversed = !isReversed;
    }

    @Override
    public T get(int index) {
        return isReversed ? elements.get(size() - index - 1) : elements.get(index);
    }

    @Override
    public int size() {
        return elements.size();
    }
}
