package queue;

/**
 * INV: size >= 0
 * if queue - empty  then  tail == head
 * if size < (capacity - head) then head < tail (elements[head..tail - 1] = queue[1..size])
 * if size > (capacity - head) then head > tail (elements[head..capacity,0..tail - 1] = queue[1..size])
 */
public class ArrayQueueADT {
    private static final int START = 1 << 5;
    private int capacity;
    private int size;
    private int head, tail;
    private Object[] elements;

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head = 0 && capacity = 2 ^ 5
     */
    public ArrayQueueADT() {
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
    public static void enqueue(ArrayQueueADT queue, Object elem) {
        ensureCapacity(queue, queue.size + 1);
        queue.size++;

        queue.elements[queue.tail] = elem;
        queue.tail = (queue.tail + 1) % queue.capacity;
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue, without changes queue
     * RES = elements[head] = queue[1] && queue' = queue
     */
    public static Object element(ArrayQueueADT queue) {
        assert queue.size > 0;
        return queue.elements[queue.head];
    }

    /**
     * pre: size > 0
     * post: Return element from head this queue and remove from queue
     * RES = elements[head] = queue[1] && queue' = queue[2..size] && size' = size - 1
     */
    public static Object dequeue(ArrayQueueADT queue) {
        assert queue.size > 0;
        queue.size--;

        int oldHead = queue.head;
        queue.head = (queue.head + 1) % queue.capacity;
        return queue.elements[oldHead];
    }

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head = 0 && capacity = 2 ^ 5
     */
    public static void clear(ArrayQueueADT queue) {
        queue.capacity = START;
        queue.head = 0;
        queue.tail = 0;
        queue.size = 0;
        queue.elements = new Object[START];
    }

    /**
     * pre: newCapacity > 0
     * post: if current capacity <= newCapacity doubles a capacity (capacity' = capacity * 2)
     * and copy exiting data in queue' in order from 0 to size (head < tail)
     * ,else returns
     */
    private static void ensureCapacity(ArrayQueueADT queue, int newCapacity) {
        if (newCapacity < queue.capacity) {
            return;
        }

        int to = (queue.head < queue.tail) ? queue.tail : queue.capacity;
        queue.capacity *= 2;
        Object[] newElements = new Object[queue.capacity];
        System.arraycopy(queue.elements, queue.head, newElements, 0, to - queue.head);
        if (queue.tail < queue.head) {
            System.arraycopy(queue.elements, 0, newElements, to - queue.head, queue.tail);
        }

        queue.elements = newElements;
        queue.tail = queue.size;
        queue.head = 0;
    }

    /**
     * pre: -
     * post: Return size this.queue, without changes in queue
     */
    public static int size(ArrayQueueADT queue) {
        return queue.size;
    }

    /**
     * pre: -
     * post: Return true, if this.queue is empty, else return false, without changes in queue
     */
    public static boolean isEmpty(ArrayQueueADT queue) {
        return queue.size == 0;
    }

    /**
     * pre: -
     * pos
     */
    public static Object[] toArray(ArrayQueueADT queue) {
        Object[] array = new Object[queue.size];
        int to = (queue.tail < queue.head)? queue.capacity : queue.tail;
        System.arraycopy(queue.elements, queue.head, array, 0, to - queue.head);
        if(queue.tail < queue.head) {
            System.arraycopy(queue.elements,0, array, to - queue.head, queue.tail);
        }
        return array;
    }
}
