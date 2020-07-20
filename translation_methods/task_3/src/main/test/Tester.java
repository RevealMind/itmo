package main.test;
import main.antlr.ProgramLexer;
import main.antlr.ProgramParser;
import main.java.Translator;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.TokenStream;
import org.junit.Test;

import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Tester {
    @Test
    public void simpleTest() throws IOException {
        String[] tests = {
                "if > 2 3 print 3 elseif > 2 3 print 2 elseif > 2 3 print 2 elseif > 2 3 print 2 elseif > 2 3 print 2",
                "if > 2 3 print 3",
                "if > 2 3 print 3 print 2",
                "if > 2 3 print 3 elseif > x 4 print 5 print 6",
                /*"if < 3 4 print 7 if > 2 3 print 2",
                "= a 2 ",
                "if && > 2 3 < 3 4 if > + 2 3 * 4 5 = a * 5 - 4 6 print 29",
                "= a && b true",
                "= a * - 5 6 7"*/
        };
        runTest(tests);
    }

    private void runTest(String[] tests) throws IOException {
        for (int i = 0; i < tests.length; i++) {
            String test = tests[i];
            Path pathToOutputFile = Paths.get("test\\test" + i + ".java");
            BufferedWriter w = Files.newBufferedWriter(pathToOutputFile);

            ProgramLexer lexer = new ProgramLexer(CharStreams.fromString(test));
            TokenStream tokens = new CommonTokenStream(lexer);
            ProgramParser parser = new ProgramParser(tokens);
            Translator translator = new Translator();
            translator.translate(parser);

            w.write(translator.getWriter());
            w.close();
        }
    }
}
