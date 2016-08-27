codeFormatter: build/codeFormatter.o
	-mkdir -p bin
	g++ -Wall -o bin/codeFormatter build/codeFormatter.o

build/codeFormatter.o: src/codeFormatter.cpp
	-mkdir -p build
	g++ -Wall -std=c++11 -Iinclude -o build/codeFormatter.o -c src/codeFormatter.cpp
