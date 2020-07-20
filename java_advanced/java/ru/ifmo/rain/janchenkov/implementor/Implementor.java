package ru.ifmo.rain.janchenkov.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;
import java.util.StringJoiner;
import java.util.stream.Collectors;
/**
 * An implementation of {@link Impler}
 * &mdash; making a default implementation of a class or interface given with
 * &mdash; making a default implementation of a class or interface given with
 * {@link implement}
 */
public class Implementor implements Impler {
    /**
     * Line separator specified to current OS
     */
    private static final String NEW_LINE = System.lineSeparator();

    /**
     * Defines end of line of code
     */
    private static final String END_LINE = ";" + NEW_LINE;

    /**
     * Defines start of block of code
     */
    private static final String BEGIN = "{" + NEW_LINE;

    /**
     * Defines end of block of code
     */
    private static final String END = "}" + NEW_LINE;

    /**
     * TAB == 4 SPACES
     */
    private static final String TAB = "    ";

    /**
     * Default space
     */
    private static final String SPACE = " ";

    /**
     * Default package that should not be printed
     */
    private static final String DEFAULT_PACKAGE = "java.lang.";

    /**
     * Adds methods to {@link Set} of {@link MethodWrapper}
     * @param methods array of methods to add
     * @param collection destination set
     */
    private void getMethods(Method[] methods, Set<MethodWrapper> collection) {
        Arrays.stream(methods)
                .filter(method -> Modifier.isAbstract(method.getModifiers()))
                .map(MethodWrapper::new)
                .collect(Collectors.toCollection(() -> collection));
    }

    /**
     * Returns all methods of tree of superclasses of token
     * @param token token of class, which methods must be saved to set
     * @return {@link Set} of {@link MethodWrapper}
     */
    private Set<MethodWrapper> getMethods(Class<?> token) {
        Set<MethodWrapper> methods = new HashSet<>();
        getMethods(token.getMethods(), methods);
        while (token != null) {
            getMethods(token.getDeclaredMethods(), methods);
            token = token.getSuperclass();
        }
        return methods;
    }

    /**
     * Return full body of method
     * @param method instance of {@link Method}, which body must be resolved
     * @return body with default return type
     */
    private String buildBody(Method method) {
        Class<?> returnType = method.getReturnType();
        if (returnType.isPrimitive()) {
            String typeName = method.getReturnType().getSimpleName();
            if (typeName.equals("boolean")) {
                return " false";
            } else if (typeName.equals("void")) {
                return "";
            } else {
                return " 0";
            }
        } else {
            return " null";
        }
    }

    /**
     * Return string of exceptions of executable
     * @param executable executable to resolve
     * @return string of exceptions which this executable throws
     */
    private String buildExceptions(Executable executable) {
        var exceptions = executable.getExceptionTypes();
        if (exceptions.length != 0) {
            var joiner = new StringJoiner(", ", " throws ", "");
            for (var exception : exceptions) {
                joiner.add(exception.getCanonicalName());
            }
            return joiner.toString();
        }
        return "";
    }

    /**
     * Return string, which consists of parameters.
     * @param parameters array of type of parameters of executable
     * @param buildType true if type is needed, false otherwise
     * @return string of parameters with type if it's needed
     */
    private String buildParameters(Class<?>[] parameters, boolean buildType) {
        var join = new StringJoiner(", ", "(", ")");
        int ind = 0;
        for (var parameter : parameters) {
            join.add((buildType ? parameter.getCanonicalName() + SPACE : "") + "arg" + ind++);
        }
        return join.toString();
    }

    /**
     * Returns type without {@link DEFAULT_PACKAGE} of type (if it has)
     * @param type to resolve
     * @return type or type without "java.lang." prefix
     */
    private String buildType(String type) {
        return type.startsWith(DEFAULT_PACKAGE) ? type.substring(DEFAULT_PACKAGE.length()) : type;
    }

    /**
     * Return full signature of executable
     * @param executable executable to resolve
     * @param token token of class executable belongs to
     * @param parameters array of types of parameters of executable
     * @return signature of executable
     */
    private String buildSignature(Executable executable, Class<?> token, Class<?>[] parameters) {
        var sb = new StringBuilder();
        sb.append(Modifier.toString(executable.getModifiers() & ~Modifier.TRANSIENT & ~Modifier.ABSTRACT)).append(SPACE);
        if (token != null) {
            sb.append(getImplName(token));
        } else {
            var method = (Method) executable;
            sb.append(buildType(method.getReturnType().getCanonicalName())).append(SPACE).append(method.getName());
        }
        sb.append(buildParameters(parameters, true));
        return sb.toString();
    }

    /**
     * Return full definition of executable
     * @param executable executable, that must be resolved
     * @param token name of class method belongs to
     * @return fully resolved string of executable
     */
    private String buildExecutable(Executable executable, Class<?> token) {
        var sb = new StringBuilder();
        var parameters = executable.getParameterTypes();
        sb.append(TAB).append(buildSignature(executable, token, parameters)).append(buildExceptions(executable))
                .append(BEGIN)
                .append(TAB).append(TAB);
        if (executable instanceof Constructor) {
            sb.append("super").append(buildParameters(parameters, false));
        } else {
            sb.append("return").append(buildBody((Method) executable));
        }
        sb.append(END_LINE).append(TAB).append(END).append(NEW_LINE);
        return sb.toString();
    }

    /**
     * Return name of generated class
     * @param token token of class, which generated name should be returned
     * @return token name with "Impl" suffix
     */
    private String getImplName(Class<?> token) {
        return token.getSimpleName() + "Impl";
    }

    /**
     * Returns head of generated java class
     * @param token token of class, which head must be resolved
     * @return head with package and class definition
     */
    private String buildHead(Class<?> token) {
        var sb = new StringBuilder();
        var packageName = token.getPackageName();
        if (!packageName.isEmpty()) {
            sb.append("package ").append(packageName).append(END_LINE).append(NEW_LINE);
        }
        sb.append("public class ").append(getImplName(token))
                .append(token.isInterface() ? " implements " : " extends ").append(token.getCanonicalName()).append(SPACE);
        return sb.toString();
    }

    /**
     * Returns resolved path of generated stuff
     * @param token token of class
     * @param root path to class
     * @param suffix suffix to add in the end
     * @return resolved path
     */
    protected Path buildPath(Class<?> token, Path root, String suffix) {
        return root.resolve(token.getCanonicalName().replace('.', File.separatorChar) + "Impl" + suffix);
    }

    /**
     * Verification if class can be implemented
     * @param token token of class
     * @param root path to class
     * @throws ImplerException if class cannot be implemented or root path is invalid
     */
    private void verification(Class<?> token, Path root) throws ImplerException {
        if (token == null || root == null) {
            throw new ImplerException("Required not-null arguments.");
        }

        if (token.isPrimitive() || token.isArray() || token == Enum.class || Modifier.isFinal(token.getModifiers())) {
            throw new ImplerException("Class cannot be implemented");
        }
        if (token.isInterface()) {
            return;
        }

        boolean isOnlyStaticMethods = true;
        for (Method method : token.getDeclaredMethods()) {
            isOnlyStaticMethods &= Modifier.isStatic(method.getModifiers());
        }
        boolean isOnlyPrivateConstructors = true;
        for (Constructor constructor : token.getDeclaredConstructors()) {
            isOnlyPrivateConstructors &= Modifier.isPrivate(constructor.getModifiers());
        }
        if (isOnlyStaticMethods && isOnlyPrivateConstructors) {
            throw new ImplerException("Class cannot be implemented");
        }
    }

    /**
     * {@inheritDoc}
     */
    public void implement(Class<?> token, Path root) throws ImplerException {
        verification(token, root);
        Path path = buildPath(token, root, ".java");
        try {
            Files.createDirectories(path.getParent());
            try (var writer = Files.newBufferedWriter(path)) {
                writer.write(buildHead(token));
                writer.write(BEGIN);
                for (var constructor : token.getDeclaredConstructors()) {
                    writer.write(buildExecutable(constructor, token));
                }
                for (var method : getMethods(token)) {
                    writer.write(buildExecutable(method.getMethod(), null));
                }
                writer.write(END);
            } catch (IOException e) {
                throw new ImplerException(e.getMessage());
            }
        } catch (IOException e) {
            throw new ImplerException("Directories cannot be created.");
        }
    }

    /**
     * A private class that stores a {@link Method}.
     * Main feature differentiang it from a simple {@link Method}
     * is its {@link MethodWrapper#equals(Object)} and {@link MethodWrapper#hashCode()}
     * methods
     */
    private class MethodWrapper {

        /**
         * A method being stored inside a wrapper
         */
        private final Method method;

        /**
         * A signature of method being stored inside a wrapper
         */
        private final String signature;

        /**
         * Constructs a method wrapper by a given method
         *
         * @param method method to store
         */
        MethodWrapper(Method method) {
            this.method = method;
            this.signature = buildSignature(method, null, method.getParameterTypes());
        }

        /**
         * Gets a method stored
         *
         * @return a method stored
         */
        public Method getMethod() {
            return method;
        }

        /**
         * Overriden equals method.
         * Compares method wrappers by their signature
         *
         * @param  rhs   a method wrapper to compare with
         * @return       whether a method wrapper given equals the stored one
         */
        public boolean equals(Object rhs) {
            if (rhs instanceof MethodWrapper) {
                return signature.equals(((MethodWrapper) rhs).signature);
            }
            return false;
        }

        /**
         * {@inheritDoc}
         */
        public int hashCode() {
            return signature.hashCode();
        }
    }
    /**
     * Main method, arguments should be only length of one (name of class to generate)
     * Usage: java Implementor <class or interface to implement>
     * @param args arguments
     */
    public static void main(String[] args) {
        if (args == null || args.length != 1) {
            System.out.println("Usage: java Implementor <full name of class or interface>.");
        } else {
            var implementor = new Implementor();
            try {
                implementor.implement(Class.forName(args[0]), Paths.get("."));
            } catch (ImplerException e) {
                System.out.println(e.getMessage());
            } catch (ClassNotFoundException e) {
                System.out.println("Class cannot be located.");
            }
        }
    }
}