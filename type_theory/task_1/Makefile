HC=ghc
GEN_SOURCES=src/Lexer.x src/Parser.y
GENERATED=src/Lexer.hs src/Parser.hs
PACKAGE=home1.zip
ifeq ($(OS),Windows_NT)
	DEL=del /f
else
	DEL=rm -f
endif

.PHONY: pack all run clean

all: main.exe

run: main.exe
	./main.exe

clean:
	cd src && $(DEL) *.o *.hi Lexer.hs Parser.hs
	$(DEL) main.exe

main.exe: $(GENERATED)
	$(HC) -O2 -i./src -tmpdir . ./src/Main.hs -o main.exe

$(GENERATED): $(GEN_SOURCES)
	alex src/Lexer.x -o src/Lexer.hs
	happy src/Parser.y -o src/Parser.hs

pack: $(GENERATED)
	zip $(PACKAGE) -r Makefile src
