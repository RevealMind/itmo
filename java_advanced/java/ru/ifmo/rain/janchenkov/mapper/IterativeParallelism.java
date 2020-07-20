package ru.ifmo.rain.janchenkov.mapper;

import info.kgeorgiy.java.advanced.concurrent.ListIP;
import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static ru.ifmo.rain.janchenkov.mapper.Utils.assertThread;
import static ru.ifmo.rain.janchenkov.mapper.Utils.startThread;

public class IterativeParallelism implements ListIP {
    private final ParallelMapper mapper;

    public IterativeParallelism() {
        mapper = null;
    }

    public IterativeParallelism(ParallelMapper mapper) {
        this.mapper = mapper;
    }

    private <T, R> R resolve(final int threads, final List<? extends T> values,
                             final Function<Stream<? extends T>, ? extends R> task,
                             final Function<Stream<? extends R>, ? extends R> joiner) throws InterruptedException {
        assertThread(threads);
        int curThreads = Math.min(threads, values.size());
        int part = values.size() / curThreads;
        final List<Stream<? extends T>> partOfTask = new ArrayList<>();
        for (int i = 0; i < curThreads; i++) {
            final int index = i;
            final int left = i * part;
            final int right = i + 1 == curThreads ? values.size() : left + part;
            partOfTask.add(values.subList(left, right).stream());
        }


        final List<R> results;
        if (mapper != null) {
            results = mapper.map(task, partOfTask);
        } else {
            final List<Thread> workers = new ArrayList<>();
            results = new ArrayList<>(Collections.nCopies(curThreads, null));
            for (int i = 0; i < curThreads; i++) {
                final int ind = i;
                startThread(workers, () -> results.set(ind, task.apply(partOfTask.get(ind))));
            }
            for (var thread : workers) {
                thread.join();
            }
        }

        return joiner.apply(results.stream());
    }

    @Override
    public String join(final int threads, final List<?> values) throws InterruptedException {
        return resolve(threads, values, x -> x.map(Object::toString).collect(Collectors.joining()), x -> x.collect(Collectors.joining()));
    }

    @Override
    public <T> List<T> filter(final int threads, final List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return resolve(threads, values, x -> x.filter(predicate).collect(Collectors.toList()), x -> x.flatMap(List::stream).collect(Collectors.toList()));
    }

    @Override
    public <T, U> List<U> map(final int threads, final List<? extends T> values, Function<? super T, ? extends U> function) throws InterruptedException {
        return resolve(threads, values, x -> x.map(function).collect(Collectors.toList()), x -> x.flatMap(List::stream).collect(Collectors.toList()));
    }

    @Override
    public <T> T maximum(final int threads, final List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        return resolve(threads, values, x -> x.max(comparator).get(), x -> x.max(comparator).get());
    }

    @Override
    public <T> T minimum(final int threads, final List<? extends T> values, Comparator<? super T> comparator) throws InterruptedException {
        return maximum(threads, values, comparator.reversed());
    }

    @Override
    public <T> boolean all(final int threads, final List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return resolve(threads, values, x -> x.allMatch(predicate), x -> x.allMatch(Boolean::booleanValue));
    }

    @Override
    public <T> boolean any(final int threads, final List<? extends T> values, Predicate<? super T> predicate) throws InterruptedException {
        return !all(threads, values, Predicate.not(predicate));
    }
}
