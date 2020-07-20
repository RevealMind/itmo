package ru.ifmo.rain.janchenkov.walk;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class RecursiveWalk {
    public static void main(String[] args) {
   /*     if (args == null || args.length != 2 || args[0] == null || args[1] == null) {
            System.out.println("ERROR: 2 non-empty elements required (input and output files)");
            return;
        }
        //System.out.println("In: " + args[0]);
        //System.out.println("Out: " + args[1 ]);
        Path in, out;

        try {
            in = Paths.get(args[0]);
        } catch (InvalidPathException e) {
            System.out.println("ERROR: invalid path for input file. (" + e.getMessage() + ").");
            return;
        }

	try {
            Path outFilePath = Path.of(args[1]);
            if (outFilePath.getParent() != null)
                Files.createDirectories(outFilePath.getParent());
	} catch (InvalidPathException | IOException | UnsupportedOperationException | SecurityException e) {
            System.out.println("ERROR: can't create directory. (" + e.getMessage() + ").");
            return;
	}
        
	try {
            out = Paths.get(args[1]);
        } catch (InvalidPathException e) {
            System.out.println("ERROR: invalid path for output file. (" + e.getMessage() + ").");
            return;
        }

        process(in, out);*/
    }

    private static void process(Path in, Path out) {
        try (BufferedReader reader = Files.newBufferedReader(in)) {
            try (BufferedWriter writer = Files.newBufferedWriter(out)) {
                try {
                    String path;
                    while ((path = reader.readLine()) != null) {
                        try {
                            //--------------------------------------walker-----------------------------------
                            try {
                                Path filePath = Paths.get(path);
                                try {
                                    Files.walkFileTree(filePath, new Visitor(writer));
                                } catch (IOException e) {
                                    writer.write(String.format("%08x", 0) + " " + filePath);
                                }
                            } catch (InvalidPathException e) {
                                writer.write(String.format("%08x", 0) + " " + path);
                            }
                            //-------------------------------------------------------------------------------
                        } catch (IOException e) {
                            System.out.println("ERROR: something went wrong when was writing to output file. (" + e.getMessage() + ").");
                        }
                    }
                } catch (IOException e) {
                    System.out.println("ERROR: something went wrong when was reading from input file. (" + e.getMessage() + ").");
                }
            } catch (IOException | UnsupportedOperationException | SecurityException e) {
                System.out.println("ERROR: can't open output file. (" + e.getMessage() + ").");
            }
        } catch (IOException | SecurityException e) {
            System.out.println("ERROR: can't open input file. (" + e.getMessage() + ").");
        }
    }

}
