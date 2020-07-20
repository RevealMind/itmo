package linked_list_set;

import kotlinx.atomicfu.AtomicRef;

public class SetImpl implements Set {
    private abstract static class Node {}

    private static class Active extends Node {
        AtomicRef<Node> next;
        int x;

        Active(Node next, int key) {
            this.next = new AtomicRef<>(next);
            this.x = key;
        }
    }

    private static class Inactive extends  Node {
        Active node;

        Inactive(Active node) {
            this.node = node;
        }
    }

    private class Window {
        Active cur, next;
    }

    private final AtomicRef<Active> head = new AtomicRef(new Active(new Active(null, Integer.MAX_VALUE), Integer.MIN_VALUE));

    /**
     * Returns the {@link Window}, where cur.x < x <= next.x
     */
    private Window findWindow(int x) {
        while (true) {
            Window w = new Window();
            w.cur = head.getValue();
            w.next = (Active) w.cur.next.getValue();

            boolean isFail = false;
            while (w.next.x < x) {
                Node next = w.next.next.getValue();
                if (next instanceof Active) {
                    w.cur = w.next;
                    w.next = (Active) next;
                } else {
                    if (!w.cur.next.compareAndSet(w.next, ((Inactive) next).node)) {
                        isFail = true;
                        break;
                    }
                }
            }

            if (!isFail) {
                return w;
            }
        }
    }

    @Override
    public boolean add(int x) {
        while (true) {
            Window w = findWindow(x);

            if (w.next.x == x && (w.next.next.getValue() instanceof Active)) {
                return false;
            }

            if (w.cur.next.compareAndSet(w.next, new Active(w.next, x))) {
                return true;
            }
        }
    }

    @Override
    public boolean remove(int x) {
        while (true) {
            Window w = findWindow(x);

            if(w.next.x != x) {
                return false;
            }

            Node next = w.next.next.getValue();

            if (next instanceof Inactive) {
                return false;
            }

            if (w.next.next.compareAndSet(next, new Inactive((Active) next))) {
                w.cur.next.compareAndSet(w.next, next);
                return true;
            }
        }
    }

    @Override
    public boolean contains(int x) {
        Window w = findWindow(x);
        return w.next.x == x && (w.next.next.getValue() instanceof Active);
    }
}