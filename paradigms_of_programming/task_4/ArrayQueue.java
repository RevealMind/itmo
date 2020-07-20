package queue;
public class ArrayQueue extends AbstractQueue {
    private final int START = 1 << 5;
    private int capacity;
    private int head, tail;
    private Object[] elements;

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head = 0 && capacity = 2 ^ 5
     */
    public ArrayQueue() {
        this.capacity = START;
        this.head = 0;
        this.tail = 0;
        this.size = 0;
        this.elements = new Object[START];
    }

    protected void add(Object elem) {
        ensureCapacity(this.size + 1);
        this.elements[this.tail] = elem;
        this.tail = (this.tail + 1) % this.capacity;
    }

    protected Object element() {
        assert this.size > 0;
        return this.elements[this.head];
    }

    protected void pop() {
        this.head = (this.head + 1) % this.capacity;
    }

    public void clear() {
        this.capacity = START;
        this.head = 0;
        this.tail = 0;
        this.size = 0;
        this.elements = new Object[START];
    }

    /**
     * pre: newCapacity > 0
     * post: if current capacity <= newCapacity doubles a capacity (capacity' = capacity * 2)
     * and copy exiting data in queue' in order from 0 to size (head < tail)
     * ,else returns
     */
    private void ensureCapacity(int newCapacity) {
        if (newCapacity < this.capacity) {
            return;
        }
        int oldCapacity = this.capacity;
        this.capacity *= 2;
        this.elements = copy(this.capacity, oldCapacity, this.tail, this.head);
        this.tail = this.size;
        this.head = 0;
    }

    /*public Object[] toArray() {
        return copy(this.size, this.capacity, this.tail, this.head);
    }*/

    /**
     * pre: capacity > length >= 0, capacity >= 0, 0 <= tail < capacity, 0 <= head < capacity
     * post: Returns array with elements of queue in order from 0 to size, without changes of queue
     */
    private Object[] copy(int length, int capacity, int tail, int head) {
        Object[] array = new Object[length];
        int to = (tail < head) ? capacity : tail;
        System.arraycopy(this.elements, head, array, 0, to - head);
        if (tail < head) {
            System.arraycopy(this.elements, 0, array, to - head, tail);
        }
        return array;
    }
}
