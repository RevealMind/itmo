    package queue;
public class LinkedQueue extends AbstractQueue{
    private Node tail, head;

    private class Node {
        Object value;
        Node next;

        Node(Object element, Node next) {
            this.value = element;
            this.next = next;
        }
    }

    protected void add(Object element) {
        if (this.size == 0) {
            this.head = this.tail = new Node(element, null);
        } else {
            this.tail.next = new Node(element, null);
            this.tail = this.tail.next;
        }
    }

    /*public Object[] toArray() {
        Object[] array = new Object[this.size];
        Node next = this.head;
        int i = 0;
        while(next != null) {
            array[i++] = next.value;
            next = next.next;
        }
        return array;
    }*/

    protected Object element() {
        assert size > 0;
        return head.value;
    }

    protected void pop() {
        this.head = this.head.next;
    }
}
