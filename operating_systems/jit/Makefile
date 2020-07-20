Compilator := g++
Flags := -std=c++11
Source := pseudojit.cpp
Exec := pseudojit

all: $(Exec)

run: $(Exec)
	./$(Exec)

$(Exec): $(Source)
	g++ -std=c++11 $(Source) -o $(Exec)
