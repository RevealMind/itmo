#Makefile
Compilator := g++
Flags := -std=c++11
Source := find.cpp
Exec := find

all: $(Exec)

run: $(Exec)
	./$(Exec)

$(Exec): $(Source)
	g++ -std=c++11 $(Source) -o $(Exec)
