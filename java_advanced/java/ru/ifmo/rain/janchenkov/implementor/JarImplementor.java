package ru.ifmo.rain.janchenkov.implementor;

import info.kgeorgiy.java.advanced.implementor.ImplerException;
import info.kgeorgiy.java.advanced.implementor.JarImpler;

import javax.tools.JavaCompiler;
import javax.tools.ToolProvider;
import java.io.File;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.CodeSource;
import java.util.Comparator;
import java.util.jar.Attributes;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;
import java.util.zip.ZipEntry;

/**
 * An implementation of {@link JarImpler}
 * &mdash; making a default implementation of a class or interface given with
 * {@link implement} or {@link implementJar}
 */
public class JarImplementor extends Implementor implements JarImpler {
    /**
     * Creates jar of class
     * @param token class, which jar file is needed
     * @param root source files folder
     * @param jarFile destination jar
     * @throws ImplerException if IO Error occured during creating
     */
    private void createJar(Class<?> token, Path root, Path jarFile) throws ImplerException {
        var manifest = new Manifest();
        var attributes = manifest.getMainAttributes();
        attributes.put(Attributes.Name.MANIFEST_VERSION, "1.0");
        try (JarOutputStream writer = new JarOutputStream(Files.newOutputStream(jarFile), manifest)) {
            writer.putNextEntry(new ZipEntry(token.getCanonicalName().replace('.', '/') + "Impl.class"));
            Files.copy(buildPath(token, root, ".class"), writer);
        } catch (IOException e) {
            throw new ImplerException("Error while writing jar file:" + e.getMessage());
        }
    }

    /**
     * Gets class path of specified class
     * @param token - class, which class path is needed
     * @throws ImplerException if class path cannot be resolved
     * @return specified class path of class
     */
    private static String getClassPath(Class<?> token) throws ImplerException {
        try {
            var source = token.getProtectionDomain().getCodeSource();
            if (source == null) {
                return ".";
            }
            return Path.of(source.getLocation().toURI()).toString();
        } catch (final URISyntaxException e) {
            throw new ImplerException("Classpath cannot be resolved " + e.getMessage());
        }
    }

    /**
     * Compiles file using specified classpath.
     * @param classPath path to class folder
     * @param filename path of file to compile
     * @throws ImplerException if the compiler is not found or the compiler terminates with a code not equal to 0
     */
    private void compile(String classPath, String filename) throws ImplerException {
        JavaCompiler compiler = ToolProvider.getSystemJavaCompiler();
        if (compiler == null) {
            throw new ImplerException("Java compiler cannot be found");
        }
        String[] args = {"-cp", classPath, filename};
        if (compiler.run(null, null, null, args) != 0) {
            throw new ImplerException("Generated files cannot be compiled ");
        }
    }

    /**
     * {@inheritDoc}
     */
    public void implementJar(Class<?> token, Path jarFile) throws ImplerException {
        if (token == null || jarFile == null) {
            throw new ImplerException("Not-null arguments expected");
        }
        try {
            Files.createDirectories(jarFile.getParent());
        } catch (IOException e) {
            throw new ImplerException("Cannot create directory for jar file" + e.getMessage());
        }
        Path tmpDir;
        try {
            tmpDir = Files.createTempDirectory(jarFile.toAbsolutePath().getParent(), "tmp");
        } catch (IOException e) {
            throw new ImplerException("Error during creating temporary directory", e);
        }
        try {
            implement(token, tmpDir);
            Path generatedFile = buildPath(token, tmpDir, ".java");
            compile(getClassPath(token), generatedFile.toString());
            createJar(token, tmpDir, jarFile);
        } finally {
            try {
                Files.walk(tmpDir)
                        .map(Path::toFile)
                        .sorted(Comparator.reverseOrder())
                        .forEach(File::delete);
            } catch (IOException e) {
                throw new ImplerException("Failed deleting temporary files in " + tmpDir.toString());
            }
        }
    }

    /**
     * Implements a given class and stores it in a given path.
     * Usage: {@code <options> <class name> <path to store>}
     * Without any flags you get a java source file implementation.
     * And using {@code -jar} option you get a jar file implementation.
     *
     * @param  args        arguments of a described rules
     */
    public static void main(String[] args) {
        if (args == null || (args.length != 2 && args.length != 3)) {
            System.out.println("Usage: java JarImplementor <full name of class or interface>");
            System.out.println("or");
            System.out.println("Usage: java JarImplementor -jar <full name of class or interface> <name of jar file>");
            return;
        }
        for (String arg : args) {
            if (arg == null) {
                System.out.println("Required not-null arguments.");
                return;
            }
        }
        try {
            JarImpler implementor = new JarImplementor();
            if (args.length == 2) {
                implementor.implement(Class.forName(args[0]), Paths.get(args[1]));
            } else if ("-jar".equals(args[0])) {
                implementor.implementJar(Class.forName(args[1]), Paths.get(".").resolve(args[2]));
            }
        } catch (ClassNotFoundException e) {
            System.out.println("Cannot locate your class");
        } catch (InvalidPathException e) {
            System.out.println("Invalid path");
        } catch (ImplerException e) {
            System.out.println(e.getMessage());
        }
    }
}
