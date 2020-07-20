import java.util.concurrent.atomic.AtomicReference
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class SynchronousQueueMS<E> : SynchronousQueue<E> {
    // TODO head and tail pointers
    private val dummy = Node()
    private val head = AtomicReference<Node>(dummy)
    private val tail = AtomicReference<Node>(dummy)

    open class Node {
        val next = AtomicReference<Node>(null)
    }

    class ReceiveWrapper<E>(val coroutine: Continuation<E>) : Node ()

    class SendWrapper<E>(var data: E, val coroutine: Continuation<Unit>) : Node ()

    override suspend fun send(element: E) {
        while (true) {
            val t = tail.get()

            if (t == head.get() || t is SendWrapper<*>) {
                val res = suspendCoroutine<Any> sc@{ continuation ->
                    val newTail = SendWrapper(element, continuation)
                    val currentTail = tail.get()

                    if ((currentTail == head.get() || currentTail is SendWrapper<*>) && currentTail.next.compareAndSet(null, newTail)) {
                        tail.compareAndSet(currentTail, newTail)
                    } else {
                        continuation.resume("RETRY")
                        return@sc
                    }
                }

                if (res == "RETRY") continue

                return
            } else {
                val currentHead = head.get();

                if (currentHead == tail.get()) continue;

                val newHead = currentHead.next.get() ?: continue

                if (newHead is ReceiveWrapper<*>) {
                    if (head.compareAndSet(currentHead, newHead)) {
                        (newHead.coroutine as Continuation<E>).resume(element)
                        return
                    }
                }
            }
        }
    }

    override suspend fun receive(): E {
        while (true) {
            val t = tail.get()

            if (t == head.get() || t is ReceiveWrapper<*>) {
                val res = suspendCoroutine<Any> sc@{ continuation ->
                    val newTail = ReceiveWrapper(continuation)
                    val currentTail = tail.get()

                    if ((currentTail == head.get() || currentTail is ReceiveWrapper<*>) && currentTail.next.compareAndSet(null, newTail)) {
                        tail.compareAndSet(currentTail, newTail)
                    } else {
                        continuation.resume("RETRY")
                        return@sc
                    }
                }

                if (res == "RETRY") continue

                return res as E;

            } else {
                val currentHead = head.get();

                if (currentHead == tail.get()) continue;

                val newHead = currentHead.next.get() ?: continue

                if (currentHead != tail.get() && newHead is SendWrapper<*>) {
                    if (head.compareAndSet(currentHead, newHead)) {
                        newHead.coroutine.resume(Unit);
                        return newHead.data as E
                    }
                }
            }
        }
    }
}
