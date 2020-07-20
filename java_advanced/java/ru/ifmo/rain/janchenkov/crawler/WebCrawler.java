package ru.ifmo.rain.janchenkov.crawler;

import info.kgeorgiy.java.advanced.crawler.*;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.*;
import java.util.concurrent.*;

public class WebCrawler implements Crawler {
    private static int DDOWNLOADERS = 4;
    private static int DEXTRACTORS = 4;
    private static int DPERHOST = 4;
    private static int DDEPTH = 2;


    private final Downloader downloader;
    private final ExecutorService downloadPoll;
    private final ExecutorService extractPoll;
    private final int perHost;
    private final Map<String, HostStorage> hostStorageMap;

    private class HostStorage {
        int count = 0;
        final Queue<Runnable> tasks = new ArrayDeque<>();

        synchronized void add(Runnable task) {
            if (count >= perHost) {
                tasks.add(task);
            } else {
                count++;
                downloadPoll.submit(task);
            }
        }

        synchronized void nextTask() {
            if (!tasks.isEmpty()) {
                downloadPoll.submit(tasks.poll());
            } else {
                count--;
            }
        }
    }

    public WebCrawler(Downloader downloader, int cdownloaders, int cextractors, int perHost) {
        downloadPoll = Executors.newFixedThreadPool(cdownloaders);
        extractPoll = Executors.newFixedThreadPool(cextractors);
        this.downloader = downloader;
        this.perHost = perHost;
        hostStorageMap = new ConcurrentHashMap<>();
    }

    @Override
    public Result download(String url, int depth) {
        final Set<String> processed = new ConcurrentSkipListSet<>();
        final Map<String, IOException> failed = new ConcurrentHashMap<>();

        final Phaser phaser = new Phaser(1);

        processed.add(url);
        goRound(url, depth, processed, phaser, failed);
        phaser.arriveAndAwaitAdvance();

        processed.removeAll(failed.keySet());
        return new Result(new ArrayList<>(processed), failed);
    }

    private void goRound(final String url,
                         final int depth,
                         final Set<String> processed,
                         final Phaser phaser,
                         final Map<String, IOException> failed) {
        String host;
        try {
            host = URLUtils.getHost(url);
        } catch (MalformedURLException e) {
            failed.put(url, e);
            return;
        }

        HostStorage hostStorage = hostStorageMap.computeIfAbsent(host, x -> new HostStorage());

        Runnable downloadTask = () -> {
            try {
                final Document document = downloader.download(url);
                if (depth > 1) {
                    Runnable extractorTask = () -> {
                        try {
                            document.extractLinks()
                                    .stream()
                                    .filter(processed::add)
                                    .forEach(link -> goRound(link, depth - 1, processed, phaser, failed));
                        } catch (IOException e) {
                            failed.put(url, e);
                        } finally {
                            phaser.arrive();
                        }
                    };

                    phaser.register();
                    extractPoll.submit(extractorTask);
                }
            } catch (IOException e) {
                failed.put(url, e);
            } finally {
                phaser.arrive();
                hostStorage.nextTask();
            }
        };

        phaser.register();
        hostStorage.add(downloadTask);
    }

    @Override
    public void close() {
        downloadPoll.shutdown();
        extractPoll.shutdown();
    }

    public static void main(String[] args) {
        if (args == null || args.length < 1) {
            System.out.println("Usage: WebCrawler url [depth [downloads [extractors [perHost]]]]");
            return;
        }

        for (String a : args) {
            if (a == null) {
                System.out.println("Params must be non-null");
                return;
            }
        }

        String url = args[0];
        int downloaders = DDOWNLOADERS;
        int extractors = DEXTRACTORS;
        int perHost = DPERHOST;
        int depth = DDEPTH;

        try {
            switch (args.length) {
                case 5:
                    perHost = parseIntArgs(args, 4);
                case 4:
                    extractors = parseIntArgs(args, 3);
                case 3:
                    downloaders = parseIntArgs(args, 2);
                case 2:
                    depth = parseIntArgs(args, 1);
            }
        } catch (IllegalArgumentException ignored) {
            System.out.println("Params must be integer numbers greater than zero");
            return;
        }

        try (Crawler crawler = new WebCrawler(new CachingDownloader(), downloaders, extractors, perHost)) {
            Result result = crawler.download(url, depth);
            System.out.println(String.format("%4d pages \t--\t downloaded\n", result.getDownloaded().size()));
            System.out.println(String.format("%4d errors\t--\t occurred", result.getErrors().size()));
        } catch (IOException e) {
            System.out.println("An error occurred while downloading. " + e.getMessage());
        }
    }

    private static int parseIntArgs(String[] args, int pos) {
        int value;
        try {
            value = Integer.parseInt(args[pos]);
            if (value < 1) {
                throw new IllegalArgumentException();
            }
        } catch (NumberFormatException e) {
            throw new IllegalArgumentException();
        }
        return value;
    }
}
