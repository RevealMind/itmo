package dijkstra

import java.util.Random
import java.util.PriorityQueue
import java.util.Queue
import java.util.concurrent.Phaser
import java.util.concurrent.locks.ReentrantLock
import kotlin.Comparator
import kotlin.concurrent.thread
import kotlinx.atomicfu.atomic

private val NODE_DISTANCE_COMPARATOR = Comparator<Node> { o1, o2 -> Integer.compare(o1!!.distance, o2!!.distance) }

class PriorityMultiQueue<T : Any>(val amount: Int, val comparator: Comparator<T>) {
    private val queues = List(amount) { PriorityQueue(amount, comparator) }
    private val locks = List(amount) { ReentrantLock(true) }
    private val rand = Random(0)

    fun add(element: T): Boolean {
        while (true) {
            val randomQueue = rand.nextInt(amount)
            if (locks[randomQueue].tryLock()) {
                try {
                    return queues[randomQueue].offer(element)
                } finally {
                    locks[randomQueue].unlock()
                }
            }
        }
    }

    fun take(): T? {
        while (true) {
            val firstQueue = rand.nextInt(amount)
            if (locks[firstQueue].tryLock()) {
                while (true) {
                    val secondQueue = rand.nextInt(amount)
                    if (locks[secondQueue].tryLock()) {
                        try {
                            return minOf(queues[firstQueue], queues[secondQueue], compareBy(nullsLast(comparator), Queue<T>::peek)).poll();
                        } finally {
                            locks[firstQueue].unlock();
                            locks[secondQueue].unlock();
                        }
                    }
                }

            }
        }
    }
}
private val activeNodes = atomic(1)

fun shortestPathParallel(start: Node) {
    val workers = Runtime.getRuntime().availableProcessors()
    start.distance = 0;

    val q = PriorityMultiQueue(2 * workers, NODE_DISTANCE_COMPARATOR)
    q.add(start)

    val onFinish = Phaser(workers + 1)
    activeNodes.lazySet(1);

    repeat(workers) {
        thread {
            while (activeNodes.value > 0) {
                val cur: Node = q.take() ?: continue
                for (edge in cur.outgoingEdges) {
                    val newWeight = cur.distance + edge.weight
                    while (true) {
                        val curWeight = edge.to.distance
                        if (curWeight > newWeight) {
                            if (!edge.to.casDistance(curWeight, newWeight)) {
                                continue
                            }
                            q.add(edge.to)
                            activeNodes.incrementAndGet()
                        }
                        break
                    }
                }
                activeNodes.decrementAndGet()
            }
            onFinish.arrive()
        }
    }
    onFinish.arriveAndAwaitAdvance()
}
