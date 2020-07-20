package ru.ifmo.rain.janchenkov.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class HelloUDPClient implements HelloClient {
    @Override
    public void run(String host, int port, String prefix, int threadsCount, int requests) {
        final InetAddress inetAddress;
        try {
            inetAddress = InetAddress.getByName(host);
        } catch (UnknownHostException e) {
            System.err.println("ERROR: Could not find host: " + host);
            return;
        }

        final InetSocketAddress socketAddress = new InetSocketAddress(inetAddress, port);

        final ExecutorService workers = Executors.newFixedThreadPool(threadsCount);
        for (int i = 0; i < threadsCount; i++) {
            final int threadId = i;

            workers.submit(() -> {
                try (DatagramSocket socket = new DatagramSocket()) {
                    socket.setSoTimeout(1000);

                    int buffSize = socket.getReceiveBufferSize();
                    byte[] buff = new byte[buffSize];
                    final DatagramPacket response = new DatagramPacket(buff, buffSize);

                    for (int requestId = 0; requestId < requests; requestId++) {
                        String requestMsg = String.format("%s%d_%d", prefix, threadId, requestId);
                        final DatagramPacket request = new DatagramPacket(requestMsg.getBytes(StandardCharsets.UTF_8),
                                requestMsg.length(), socketAddress);

                        while (!socket.isClosed() || Thread.currentThread().isInterrupted()) {
                            try {
                                socket.send(request);

                                System.out.println("Request: " + requestMsg);
                                socket.receive(response);

                                String responseMsg = new String(response.getData(),
                                        response.getOffset(), response.getLength(), StandardCharsets.UTF_8);

                                if (responseMsg.length() != requestMsg.length() &&
                                        (responseMsg.endsWith(requestMsg))) {
                                    System.out.println("Response: " + responseMsg);
                                    break;
                                }
                            } catch (IOException e) {
                                System.out.println("ERROR: " + e.getMessage());
                            }
                        }
                    }
                } catch (SocketException e) {
                    System.out.println("ERROR: Could not create socket to server: " + socketAddress.toString());
                }
            });
        }

        workers.shutdown();

        try {
            workers.awaitTermination(threadsCount * requests, TimeUnit.MINUTES);
        } catch (InterruptedException ignored) {
        }
    }

    public static void main(String[] args) {
        if (args == null || args.length != 5) {
            System.err.println("Usage: HelloUDPServer [host] [port] [prefix] [threadsCount] [requestCount]");
        }

        for (String a : args) {
            if (a == null) {
                System.out.println("Params must be non-null");
                return;
            }
        }

        try {
            new HelloUDPClient().run(args[0],
                    Integer.parseInt(args[1]),
                    args[2],
                    Integer.parseInt(args[3]),
                    Integer.parseInt(args[4]));
        } catch (NumberFormatException e) {
            System.err.println("ERROR: Integer args expected");
        }
    }
}