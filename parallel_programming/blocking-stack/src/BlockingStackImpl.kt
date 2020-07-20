import java.util.concurrent.atomic.*
import kotlin.coroutines.Continuation
import kotlin.coroutines.resume
import kotlin.coroutines.suspendCoroutine

class BlockingStackImpl<E> : BlockingStack<E> {

    // ==========================
    // Segment Queue Synchronizer
    // ==========================

    private val enqIdx: AtomicReference<Receiver<E>>
    private val deqIdx: AtomicReference<Receiver<E>>

    init {
        val dummy = Receiver<E>(null)
        enqIdx = AtomicReference(dummy);
        deqIdx = AtomicReference(dummy);
    }

    private suspend fun suspend(): E {
        return suspendCoroutine { continuation ->
            val newTail = Receiver(continuation);

            while (true) {
                val currentTail = deqIdx.get()

                if (currentTail.next.compareAndSet(null, newTail)) {
                    deqIdx.compareAndSet(currentTail, newTail)
                    break
                }
            }
        }
    }

    private fun resume(element: E) {
        while (true) {
            val currentHead = enqIdx.get()

            if (currentHead == deqIdx.get()) continue

            val newHead = currentHead.next.get() ?: continue

            if (enqIdx.compareAndSet(currentHead, newHead)) {
                newHead.coroutine?.resume(element)
                return
            }
        }
    }

    // ==============
    // Blocking Stack
    // ==============


    private val head = AtomicReference<Node<E>?>()
    private val elements = AtomicInteger()

    override fun push(element: E) {
        val elements = this.elements.getAndIncrement()

        if (elements >= 0) {
            while (true) {
                val currentHead = head.get()

                if (currentHead?.element == SUSPENDED) {
                    val newHead = currentHead.next.get();

                    if (head.compareAndSet(currentHead, newHead)) {
                        resume(element)
                        return
                    }
                } else {
                    val newHead = Node(element, AtomicReference(currentHead))

                    if (head.compareAndSet(currentHead, newHead)) break
                }
            }
        } else {
            resume(element)
        }
    }

    override suspend fun pop(): E {
        val elements = this.elements.getAndDecrement()
        if (elements > 0) {
            while (true) {
                val currentHead = head.get()

                if (currentHead == null) {
                    val newHead = Node<E>(SUSPENDED, AtomicReference(null))

                    if (head.compareAndSet(currentHead, newHead)) {
                        return suspend()
                    }
                } else {
                    val newHead = currentHead.next.get()

                    if (head.compareAndSet(currentHead, newHead)) {
                        return currentHead.element as E
                    }
                }
            }
        } else {
            return suspend()
        }
    }
}

private class Node<E>(val element: Any?, val next: AtomicReference<Node<E>?>)

private class Receiver<E>(val coroutine: Continuation<E>?, val next: AtomicReference<Receiver<E>?> = AtomicReference())

private val SUSPENDED = Any()