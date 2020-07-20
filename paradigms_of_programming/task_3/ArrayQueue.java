package queue;

/**
 * INV: size >= 0
 * if queue - empty  then  tail == head
 * if size < (capacity - head) then head < tail (elements[head..tail - 1] = queue[1..size])
 * if size > (capacity - head) then head > tail (elements[head..capacity,0..tail - 1] = queue[1..size])
 */
public class ArrayQueue {
    private final int START = 1 << 5;
    private int capacity;
    private int size;
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

    /**
     * pre: -
     * post: Adds element to the tail of this.queue
     * queue'[1..size] = queue[1..size] && queue[size'] = elem && size' = size + 1
     */
    public void enqueue(Object elem) {
        ensureCapacity(this.size + 1);
        this.size++;

        this.elements[this.tail] = elem;
        this.tail = (this.tail + 1) % this.capacity;
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue, without changes queue
     * RES = elements[head] = queue[1] && queue' = queue
     */
    public Object element() {
        assert this.size > 0;
        return this.elements[this.head];
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue and remove from queue
     * RES = elements[head] = queue[1] && queue' = queue[2..size] && size' = size - 1
     */
    public Object dequeue() {
        assert this.size > 0;
        this.size--;

        int oldHead = this.head;
        this.head = (this.head + 1) % this.capacity;
        return this.elements[oldHead];
    }

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head = 0 && capacity = 2 ^ 5
     */
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

        int to = (this.head < this.tail) ? this.tail : this.capacity;
        this.capacity *= 2;
        Object[] newElements = new Object[this.capacity];
        System.arraycopy(this.elements, this.head, newElements, 0, to - this.head);
        if (this.tail < this.head) {
            System.arraycopy(this.elements, 0, newElements, to - this.head, this.tail);
        }

        this.elements = newElements;
        this.tail = this.size;
        this.head = 0;
    }

    /**
     * pre: -
     * post: Return size this.queue, without changes in queue
     */
    public int size() {
        return this.size;
    }

    /**
     * pre: -
     * post: Return true, if this.queue is empty, else return false, without changes in queue
     */
    public boolean isEmpty() {
        return this.size == 0;
    }

    /**
     * pre: -
     * post: Returns array with elements of queue in order from 0 to size, without changes of queue
     */
    public Object[] toArray() {
        Object[] array = new Object[this.size];
            int to = (this.tail < this.head)? this.capacity : this.tail;
        System.arraycopy(this.elements, this.head, array, 0, to - this.head);
        if(this.tail < this.head) {
            System.arraycopy(this.elements,0, array, to - this.head, this.tail);
        }
        return array;
    }
}
