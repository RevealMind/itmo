all: build_utils build_server build_client

build_utils:
	g++ -std=c++11 -Wall -c -o utils.o utils.cpp

build_server:
	g++ -std=c++11 -Wall -o server.o server.cpp

build_client:
	g++ -std=c++11 -Wall -o client.o client.cpp

server: server.o 
	./server.o name

client: client.o
	./client.o name file.txt

clean:
	rm -f *.o *.txt