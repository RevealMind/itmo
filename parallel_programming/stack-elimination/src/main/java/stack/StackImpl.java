package stack;

import kotlinx.atomicfu.*;


import java.util.Random;

public class StackImpl implements Stack {
    private static class Node {
        final AtomicRef<Node> next;
        final int x;

        Node(int x, Node next) {
            this.next = new AtomicRef<>(next);
            this.x = x;
        }
    }

    // head pointer
    private AtomicRef<Node> head = new AtomicRef<>(null);

    private final int CAPACITY = 8;

    private final Random random = new Random();
    //Elimination
    private AtomicArray<Integer> cells = new AtomicArray<>(CAPACITY);

    @Override
    public void push(int x) {
        if (tryPush(x)) {
            return;
        }
        Node newHead;
        Node oldHead;
        while (true) {
            oldHead = head.getValue();
            newHead = new Node(x, oldHead);
            if (head.compareAndSet(oldHead, newHead)) {
                return;
            }
        }
    }

    private boolean tryPush(Integer x) {
        int pos = random.nextInt(CAPACITY);
        for (int i = 0; i < CAPACITY / 2; i++) {
            if (cells.get(pos).compareAndSet(null, x)) {
                for (int wait = 0; wait < 500; wait++) {
                    if (cells.get(pos).compareAndSet(null, null)) {
                        return true;
                    }
                }
                return !cells.get(pos).compareAndSet(x, null);
            }
            pos = (pos + 1) % CAPACITY;
        }
        return false;
    }

    @Override
    public int pop() {
        Node oldHead;
        Integer x = tryPop();
        if (x != null) {
            return x;
        }
        while (true) {
            oldHead = head.getValue();
            if (oldHead == null) {
                return Integer.MIN_VALUE;
            }
            if (head.compareAndSet(oldHead, oldHead.next.getValue())) {
                return oldHead.x;
            }
        }
    }

    private Integer tryPop() {
        int pos = random.nextInt(CAPACITY);
        for (int i = 0; i < CAPACITY / 2; i++) {
            if (cells.get(pos).compareAndSet(null, null)) {
                pos = (pos + 1) % CAPACITY;
            } else {
                return cells.get(pos).getAndSet(null);
            }
        }
        return null;
    }
}
