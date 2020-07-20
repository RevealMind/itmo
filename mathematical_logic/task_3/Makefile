PROJECTNAME = translate
MAIN = Main.hs
SOURCES = Intuitionistic.hs Expression.hs Utils.hs
PREPARE = ExpressionParser.hs FirstLineParser.hs Lexer.hs

all: $(PROJECTNAME)

run:
	./$(PROJECTNAME)
	
noopt: $(PREPARE) $(MAIN) $(SOURCES)
	ghc $(MAIN) -o $(PROJECTNAME)

pack:
	zip translate.zip -r Makefile $(PREPARE) $(SOURCES) $(MAIN)

clean:
	rm -f *.o *.hi $(PREPARE) *.o *.hi
	
$(PROJECTNAME): $(PREPARE) $(MAIN) $(SOURCES)
	ghc $(MAIN) -O2 -o $(PROJECTNAME)

$(PREPARE): $(HAPPY) $(ALEX)
	happy ExpressionParser.y
	happy FirstLineParser.y
	alex Lexer.x