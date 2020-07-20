package ru.ifmo.rain.janchenkov.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class HelloUDPServer implements HelloServer {
    private ExecutorService workers;
    private ExecutorService receiver;
    private DatagramSocket socket;

    public HelloUDPServer() {
        socket = null;
        workers = null;
    }

    @Override
    public void start(int port, int threadsCount) {
        try {
            socket = new DatagramSocket(port);
        } catch (SocketException e) {
            System.err.println("ERROR: the socket could not bind to the port № " + port);
            return;
        }

        workers = Executors.newFixedThreadPool(threadsCount);
        receiver = Executors.newSingleThreadExecutor();

        receiver.submit(() -> {
            while (!socket.isClosed() && !Thread.currentThread().isInterrupted()) {
                try {
                    int buffSize = socket.getReceiveBufferSize();
                    final byte[] buff = new byte[buffSize];
                    final DatagramPacket input = new DatagramPacket(buff, buffSize);
                    socket.receive(input);
                    workers.submit(() -> sendResp(input));
                } catch (SocketException e) {
                    if (!socket.isClosed())
                        System.err.println("ERROR: Error with socket. " + e.getMessage());
                } catch (IOException e) {
                    if (!socket.isClosed())
                        System.err.println("ERROR: " + e.getMessage());
                }

            }
        });
    }

    private void sendResp(final DatagramPacket input) {
        try {
            final DatagramPacket respond = new DatagramPacket(new byte[0], 0, input.getSocketAddress());

            String respondMsg = new String(input.getData(),
                    input.getOffset(), input.getLength(), StandardCharsets.UTF_8);

            respond.setData(("Hello, " + respondMsg).getBytes(StandardCharsets.UTF_8));

            socket.send(respond);
        } catch (IOException e) {
            if (!socket.isClosed())
                System.err.println("ERROR: " + e.getMessage());
        }

    }

    @Override
    public void close() {
        socket.close();
        receiver.shutdownNow();
        workers.shutdownNow();
        try {
            workers.awaitTermination(5, TimeUnit.SECONDS);
        } catch (InterruptedException ignored) {

        }
    }

    public static void main(String[] args) {
        if (args == null || args.length < 2) {
            System.err.println("Usage: HelloUDPServer [port] [threadsCount]");
        }

        for (String a : args) {
            if (a == null) {
                System.out.println("Params must be non-null");
                return;
            }
        }

        try {
            new HelloUDPServer().start(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        } catch (NumberFormatException e) {
            System.err.println("ERROR: Integer args expected");
        }
    }
}
