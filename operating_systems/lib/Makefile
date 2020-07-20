GCC := g++ -std=c++11
STATIC := binpow
DYNAMIC := fact
DYNAMICLINKED := gcd
MAIN := main

all: main

run: main
	./main

main: main.o lib$(STATIC).a lib$(DYNAMIC).so lib$(DYNAMICLINKED).so  
	$(GCC) main.o -L. lib$(STATIC).a -l$(DYNAMIC) -Wl,-rpath,. -ldl -o main

main.o: main.cpp
	$(GCC) -c main.cpp -o main.o 

lib$(STATIC).a: $(STATIC).o
	ar rcs lib$(STATIC).a $(STATIC).o

$(STATIC).o: $(STATIC).hpp $(STATIC).cpp
	$(GCC) -c $(STATIC).cpp -o $(STATIC).o


lib$(DYNAMIC).so: $(DYNAMIC).o
	$(GCC) -shared -o lib$(DYNAMIC).so $(DYNAMIC).o

$(DYNAMIC).o: $(DYNAMIC).hpp $(DYNAMIC).cpp
	$(GCC) -fPIC -c $(DYNAMIC).cpp -o $(DYNAMIC).o

lib$(DYNAMICLINKED).so: $(DYNAMICLINKED).o
	$(GCC) -shared -o lib$(DYNAMICLINKED).so $(DYNAMICLINKED).o

$(DYNAMICLINKED).o: $(DYNAMICLINKED).hpp $(DYNAMICLINKED).cpp
	$(GCC) -fPIC -c $(DYNAMICLINKED).cpp -o $(DYNAMICLINKED).o

clean: 
	rm -rf main *.a *.o *.so