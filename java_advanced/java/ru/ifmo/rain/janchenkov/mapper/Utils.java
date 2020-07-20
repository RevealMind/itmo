package ru.ifmo.rain.janchenkov.mapper;

import java.util.List;

public class Utils {
    public static void assertThread(int threads){
        if (threads <= 0) {
            throw new IllegalArgumentException("Threads quantity must be greater than 0");
        }
    }

    public static void startThread(List<Thread> list, Runnable task) {
        var thread = new Thread(task);
        list.add(thread);
        thread.start();
    }
}
