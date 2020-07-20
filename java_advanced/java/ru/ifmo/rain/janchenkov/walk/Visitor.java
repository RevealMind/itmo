package ru.ifmo.rain.janchenkov.walk;

import java.io.BufferedInputStream;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.BasicFileAttributes;

import static java.nio.file.FileVisitResult.CONTINUE;

public class Visitor extends SimpleFileVisitor<Path> {
    private BufferedWriter writer;

    Visitor(BufferedWriter wr) {
        super();
        writer = wr;
    }

    private FileVisitResult writeToFile(int hash, String filePath) throws IOException {
        writer.write(String.format("%08x", hash) + " " + filePath);
        writer.newLine();
        return CONTINUE;
    }

    @Override
    public FileVisitResult visitFile(Path path, BasicFileAttributes basicFileAttributes) throws IOException {
        int h = 0x811c9dc5;
        try (BufferedInputStream reader = new BufferedInputStream(Files.newInputStream(path))) {
            byte[] buffer = new byte[1024];
            int cnt;
            while ((cnt = reader.read(buffer)) != -1) {
                for (int i = 0; i < cnt; i++) {
                    h = (h * 0x01000193) ^ (buffer[i] & 0xff);
                }
            }
        } catch (IOException e) {
            return writeToFile(0, path.toString());
        }
        return writeToFile(h, path.toString());
    }

    @Override
    public FileVisitResult visitFileFailed(Path path, IOException e) throws IOException {
        return writeToFile(0, path.toString());
    }
}