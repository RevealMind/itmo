package queue;

/**
 * INV: size >= 0
 * if queue - empty  then  tail == head
 * if size < (capacity - head) then head < tail (elements[head..tail - 1] = queue[1..size])
 * if size > (capacity - head) then head > tail (elements[head..capacity,0..tail - 1] = queue[1..size])
 */
public class ArrayQueueModule {
    private static final int START = 1 << 5;
    private static int capacity = START;
    private static int size = 0;
    private static int head = 0, tail = 0;
    private static Object[] elements = new Object[START];

    /**
     * pre: -
     * post: Adds element to the tail of this.queue
     * queue'[1..size] = queue[1..size] && queue[size'] = elem && size' = size + 1
     */
    public static void enqueue(Object elem) {
        ensureCapacity(size + 1);
        size++;

        elements[tail] = elem;
        tail = (tail + 1) % capacity;
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue, without changes queue
     * RES = elements[head] = queue[1] && queue' = queue
     */
    public static Object element() {
        assert size > 0;
        return elements[head];
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue and remove from queue
     * RES = elements[head] = queue[1] && queue' = queue[2..size] && size' = size - 1
     */
    public static Object dequeue() {
        assert size > 0;
        size--;

        int oldHead = head;
        head = (head + 1) % capacity;
        return elements[oldHead];
    }

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head' = 0 && capacity = 2 ^ 5
     */
    public static void clear() {
        capacity = START;
        head = 0;
        tail = 0;
        size = 0;
        elements = new Object[START];
    }

    /**
     * pre: newCapacity > 0
     * post: if current capacity <= newCapacity doubles a capacity (capacity' = capacity * 2)
     * and copy exiting data in queue' in order from 0 to size (head' < tail')
     * ,else returns
     */
    private static void ensureCapacity(int newCapacity) {
        if (newCapacity < capacity) {
            return;
        }
        int oldCapacity = capacity;
        capacity *= 2;
        elements = copy(capacity, oldCapacity, tail, head);
        tail = size;
        head = 0;
    }

    /**
     * pre: -
     * post: Return size this.queue, without changes in queue
     */
    public static int size() {
        return size;
    }

    /**
     * pre: -
     * post: Return true, if this.queue is empty, else return false, without changes in queue
     */
    public static boolean isEmpty() {
        return size == 0;
    }

    /**
     * pre: -
     * post: Returns array with elements of queue in order from 0 to size, without changes of queue
     */
    public static Object[] toArray() {
        return copy(size, capacity, tail, head);
    }

    /**
     * pre: capacity > length >= 0, capacity >= 0, 0 <= tail < capacity, 0 <= head < capacity
     * post: Returns array with elements of queue in order from 0 to size, without changes of queue
     */
    public static Object[] copy(int length, int capacity, int tail, int head) {
        Object[] array = new Object[length];
        int to = (tail < head) ? capacity : tail;
        System.arraycopy(elements, head, array, 0, to - head);
        if (tail < head) {
            System.arraycopy(elements, 0, array, to - head, tail);
        }
        return array;
    }
}
