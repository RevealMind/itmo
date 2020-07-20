package main.java;

import main.antlr.ProgramLexer;
import main.antlr.ProgramParser;
import org.antlr.v4.runtime.*;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Formatter {
    public static void main(String[] args) throws IOException {
        Path pathToInputFile = Paths.get("test.in");
        Path pathToOutputFile = Paths.get("test\\test.java");
        var w = Files.newBufferedWriter(pathToOutputFile);
        ProgramLexer lexer = new ProgramLexer(CharStreams.fromPath(pathToInputFile));
        TokenStream tokens = new CommonTokenStream(lexer);
        ProgramParser parser = new ProgramParser(tokens);
        Translator translator = new Translator();
        translator.translate(parser);
        w.write(translator.getWriter());
        w.close();
    }

}
