package msqueue;

import kotlinx.atomicfu.*;

public class MSQueue implements Queue {
    private AtomicRef<Node> head = new AtomicRef<>(null);
    private AtomicRef<Node> tail = new AtomicRef<>(null);

    public MSQueue() {
        Node dummy = new Node(0);
        this.head.setValue(dummy);
        this.tail.setValue(dummy);
    }

    private class Node {
        final int x;
        final AtomicRef<Node> next;

        Node(int x) {
            this.x = x;
            this.next = new AtomicRef<>(null);
        }
    }

    @Override
    public void enqueue(int x) {
        Node node = new Node(x);
        Node curTail;
        AtomicRef<Node> next;
        while (true) {
            curTail = tail.getValue();
            next = curTail.next;
            if (tail.getValue() == curTail) {
                if (curTail.next.compareAndSet(null, node)) {
                    break;
                } else {
                    tail.compareAndSet(curTail, next.getValue());
                }
            }
        }
        tail.compareAndSet(curTail, node);
    }

    @Override
    public int dequeue() {
        Node curHead;
        Node curTail;
        Node next;
        while (true) {
            curHead = head.getValue();
            curTail = tail.getValue();
            next = curHead.next.getValue();
            if (curHead == head.getValue()) {
                if (curHead == curTail) {
                    if (next == null) {
                        return Integer.MIN_VALUE;
                    }
                    tail.compareAndSet(curTail, next);
                } else {
                    if (head.compareAndSet(curHead, next)) {
                        return next.x;
                    }
                }
            }
        }
    }

    @Override
    public int peek() {
        Node curHead;
        Node curTail;
        Node next;
        while (true) {
            curHead = head.getValue();
            curTail = tail.getValue();
            next = curHead.next.getValue();
            if (curHead == head.getValue()) {
                if (curHead == curTail) {
                    if (next == null) {
                        return Integer.MIN_VALUE;
                    }
                    tail.compareAndSet(curTail, next);
                } else {
                    if (head.getValue() == curHead) {
                        return next.x;
                    }
                }
            }
        }
    }
}