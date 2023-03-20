all: directory arbol clear
DIRECTORY=output
COMPILER=g++

directory:
	mkdir -p $(DIRECTORY)


arbol.o: main.cpp
	$(COMPILER) -c main.cpp -o $(DIRECTORY)/arbol.o -std=c++11 -Wpedantic

arbol: arbol.o
	$(COMPILER) $(DIRECTORY)/arbol.o -o $(DIRECTORY)/arbol

clear:
	rm $(DIRECTORY)/*.o
