all: proga

run: proga
	./proga

proga: Main.hs Lexer.hs ExpressionParser.hs FirstLineParser.hs
	ghc -O2 Main.hs -o proga

Lexer.hs: Lexer.x
	alex Lexer.x

ExpressionParser.hs: ExpressionParser.y
	happy ExpressionParser.y

FirstLineParser.hs: FirstLineParser.y
	happy FirstLineParser.y

pack:
	zip home2.zip -r Makefile *.hs *.y *.x

clean:
	rm *.hi *.o Lexer.hs FirstLineParser.hs ExpressionParser.hs
