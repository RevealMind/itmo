package queue;
public interface Queue {
    /**
     * pre: -
     * post: Adds element to the tail of this.queue
     * queue'[1..size] = queue[1..size] && queue[size'] = elem && size' = size + 1
     */
    void enqueue(Object elem);


    /**
     * pre: size > 0
     * post: Return element from head this queue, without changes queue
     * RES = elements[head] = queue[1] && queue' = queue
     */
    Object element();

    /**
     * pre: size > 0
     * post: Return element from head this queue and remove from queue
     * RES = elements[head] = queue[1] && queue' = queue[2..size] && size' = size - 1
     */
    Object dequeue();

    /**
     * pre: -
     * post: Removes all elements of queue
     * size' = tail' = head = 0 && capacity = 2 ^ 5
     */
    void clear();

    /**
     * pre: -
     * post: Return size this.queue, without changes in queue
     */
    int size();

    /**
     * pre: -
     * post: Return true, if this.queue is empty, else return false, without changes in queue
     */
    boolean isEmpty();

    /**
     * pre: -
     * post: Returns array with elements of queue in order from 0 to size, without changes of queue
     */
    Object[] toArray();
}
