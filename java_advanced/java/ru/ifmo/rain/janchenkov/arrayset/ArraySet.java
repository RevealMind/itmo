package ru.ifmo.rain.janchenkov.arrayset;

import java.util.*;

public class ArraySet<T> extends AbstractSet<T> implements NavigableSet<T> {
    private final List<T> elements;

    private final Comparator<? super T> comparator;

    public ArraySet() {
	comparator = null;
        elements = Collections.emptyList();
    }

    public ArraySet(Collection<? extends T> collection) {
        comparator = null;
	elements = new ArrayList<>(new TreeSet<>(collection));
    }

    public ArraySet(Collection<? extends T> collection, Comparator<? super T> cmp) {
        comparator = cmp;
        NavigableSet<T> sortedSet = new TreeSet<>(comparator);
        sortedSet.addAll(collection);
    	elements = new ArrayList<>(sortedSet); 
    }

    @Override
    public int size() {
        return elements.size();
    }

    @Override
    public Iterator<T> iterator() {
        return Collections.unmodifiableList(elements).iterator();
    }

    @Override
    public boolean contains(Object o) {
        return Collections.binarySearch(elements, (T) Objects.requireNonNull(o), comparator) >= 0;
    }

    private int findIndex(T key, boolean isTail, boolean isInclusive) {
        int index = Collections.binarySearch(elements, key, comparator);
        if (isTail) {
            return index < 0 ? ~index - 1 : (isInclusive ? index : index - 1);
        } else {
            return index < 0 ? ~index : (isInclusive ? index : index + 1);
        }
    }

    private T find(T element, boolean isTail, boolean isInclusive) {
        int index = findIndex(element, isTail, isInclusive);
        return (index >= 0 && index < size()) ? elements.get(index) : null;
    }

    @Override
    public T lower(T t) {
        return find(t, true, false);
    }

    @Override
    public T floor(T t) {
        return find(t, true, true);
    }

    @Override
    public T ceiling(T t) {
        return find(t, false, true);
    }

    @Override
    public T higher(T t) {
        return find(t, false, false);
    }

    @Override
    public T pollFirst() {
        throw new UnsupportedOperationException();
    }

    @Override
    public T pollLast() {
        throw new UnsupportedOperationException();
    }

    @Override
    public NavigableSet<T> descendingSet() {
	ReversedList<T> revList = new ReversedList<>(elements);
        revList.reverse();
        return new ArraySet<>(revList, Collections.reverseOrder(comparator));
    }

    @Override
    public Iterator<T> descendingIterator() {
        return descendingSet().iterator();
    }

    @Override
    public NavigableSet<T> subSet(T fromElement, boolean fromInclusive, T toElement, boolean toInclusive) {
        int head = findIndex(fromElement, false, fromInclusive);
        int tail = findIndex(toElement, true, toInclusive) + 1;
        if (tail + 1 == head) {
            tail = head;
        }
        return new ArraySet<>(elements.subList(head, tail), comparator);
    }

    @Override
    public NavigableSet<T> headSet(T toElement, boolean inclusive) {
        int index = findIndex(toElement, true, inclusive) + 1;
        return new ArraySet<>(elements.subList(0, index), comparator);
    }

    @Override
    public NavigableSet<T> tailSet(T fromElement, boolean inclusive) {
        int index = findIndex(fromElement, false, inclusive);
        return new ArraySet<>(elements.subList(index, elements.size()), comparator);
    }

    @Override
    public SortedSet<T> subSet(T fromElement, T toElement) {
        return subSet(fromElement, true, toElement, false);
    }

    @Override
    public SortedSet<T> headSet(T toElement) {
        return headSet(toElement, false);
    }

    @Override
    public SortedSet<T> tailSet(T fromElement) {
        return tailSet(fromElement, true);
    }

    @Override
    public Comparator<? super T> comparator() {
        return comparator;
    }

    @Override
    public T first() {
        if (elements.isEmpty()) {
            throw new NoSuchElementException();
        }
        return elements.get(0);
    }

    @Override
    public T last() {
        if (elements.isEmpty()) {
            throw new NoSuchElementException();
        }
        return elements.get(size() - 1);
    }
}
