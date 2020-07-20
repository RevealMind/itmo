package queue;

public abstract class AbstractQueue implements Queue {
    protected int size;

    protected abstract void add(Object element);

    protected abstract void pop();

    public void enqueue(Object element) {
        add(element);
        size++;
    }

    protected abstract Object element();

    public Object dequeue() {
        Object element = this.element();
        pop();
        size--;
        return element;
    }

    public void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }


    public Object[] toArray() {
        Object[] array = new Object[size];
        for (int i = 0; i < size; i++) {
            array[i] = dequeue();
            enqueue(array[i]);
        }
        return array;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

}
