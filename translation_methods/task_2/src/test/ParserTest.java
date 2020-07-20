import main.Parser;
import main.ParserException;
import main.Tree;
import main.Visualizer;
import org.junit.Test;


import java.io.IOException;
import java.io.InputStreamReader;


public class ParserTest {
    @Test
    public void simpleTest() throws Exception {
        String[] tests = {
                "(a and b) or not (c xor (a or not b))",
        };
        runCorrect(tests, "simple");
    }

    @Test
    public void bracketTest() throws Exception {
        String[] tests = {
                "a or b xor c or a xor d",
                "(c and a or b) xor d",
                "(a or b and c)",
                "a and (b or c xor d) or not a",
                "not (not a and b and (c or d xor e))",
                "not not a",
                "a or b xor c and d or e and f xor not g"
        };
        runCorrect(tests, "bracket");
    }

    @Test
    public void incorrectTest() throws Exception {
        String[] tests = {
            "",
            "a xom b",
            "a and or",
            "(a and b))",
            "a and b c",
            "aac or b",
            "a anf b",
            "a on b",
            "a and"
        };
        runIncorrect(tests, "simple");
    }

    private void runIncorrect(String[] tests, String simple) throws Exception {
        for (int i = 0; i < tests.length; i++) {
            String test = tests[i];
            try {
                Parser parser = new Parser();
                parser.parse(test);
            } catch (ParserException e) {
                continue;
            }
            throw new Exception("Expected fail in test: " + test);
        }
    }

    private void runCorrect(String[] tests, String type) throws Exception {
        for (int i = 0; i < tests.length; i++) {
            String test = tests[i];
            Parser parser = new Parser();
            try {
                Tree root = parser.parse(test);
                visualize(root, type + "CorrectTest" + i);
            } catch (ParserException e) {
                throw new Exception( test + " must be correct",  e);
            }
        }
    }

    private void visualize(Tree root, String filename) throws IOException, InterruptedException {
        Visualizer treeVisualizer = new Visualizer();
        treeVisualizer.printToFile(filename, root);
        String path = System.getProperty("user.dir") + "\\graph\\" + filename;
        new ProcessBuilder("dot.exe", "-Tpng", path + ".dot", "-o", path + ".png")
                .redirectError(ProcessBuilder.Redirect.INHERIT)
                .start()
                .waitFor();
    }
}
