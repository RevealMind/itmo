package ru.ifmo.rain.janchenkov.mapper;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;

import static ru.ifmo.rain.janchenkov.mapper.Utils.assertThread;
import static ru.ifmo.rain.janchenkov.mapper.Utils.startThread;

public class ParallelMapperImpl implements ParallelMapper {
    private final List<Thread> workers;
    private final Queue<Runnable> tasks;

    private class Results<T> {
        private final List<T> store;
        private int done = 0;

        Results(int size) {
            store = new ArrayList<>(Collections.nCopies(size, null));
        }

        void set(int ind, T elem) {
            store.set(ind, elem);
            synchronized (this) {
                if (++done == store.size()) {
                    notify();
                }
            }
        }

        synchronized List<T> get() throws InterruptedException {
            while (done < store.size()) {
                wait();
            }
            return store;
        }
    }

    private void doTask() throws InterruptedException {
        Runnable task;
        synchronized (tasks) {
            while (tasks.isEmpty()) {
                tasks.wait();
            }
            task = tasks.poll();
            tasks.notifyAll();
        }
        task.run();
    }

    public ParallelMapperImpl(int threads) {
        assertThread(threads);
        tasks = new ArrayDeque<>();
        workers = new ArrayList<>(threads);

        for (int i = 0; i < threads; i++) {
            startThread(workers, () -> {
                try {
                    while (!Thread.interrupted()) {
                        doTask();
                    }
                } catch (InterruptedException ignored){

                } finally {
                    Thread.currentThread().interrupt();
                }
            });
        }
    }

    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> function, List<? extends T> list) throws InterruptedException {
        Results<R> results = new Results<>(list.size());

        for (int i = 0; i < list.size(); i++) {
            final int ind = i;
            synchronized (tasks) {
                tasks.add(() -> results.set(ind, function.apply(list.get(ind))));
                tasks.notifyAll();
            }
        }

        return results.get();
    }

    @Override
    public void close() {
        workers.forEach(Thread::interrupt);
        for (var worker : workers) {
            try {
                worker.join();
            } catch (InterruptedException ignored) {

            }
        }
    }
}
