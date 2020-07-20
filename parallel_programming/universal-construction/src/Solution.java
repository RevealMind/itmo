public class Solution implements AtomicCounter {
    // объявите здесь нужные вам поля
    private final Node root = new Node(0);
    private final ThreadLocal<Node> last = ThreadLocal.withInitial(() -> root);

    public int getAndAdd(int x) {
        Node node;
        int res = 0;
        do {
            int upd = last.get().val;
            res = upd;
            upd += x;
            node = new Node(upd);
            last.set(last.get().next.decide(node));
        } while (last.get() != node);
        return res;
    }

    // вам наверняка потребуется дополнительный класс
    private static class Node {
        private final int val;
        private final Consensus<Node> next = new Consensus<>();

        public Node(int x) {
            val = x;
        }
    }
}
