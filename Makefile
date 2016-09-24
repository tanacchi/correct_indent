code_formatter: build/code_formatter.o
	-mkdir -p bin
	g++ -Wall -o bin/code_formatter build/code_formatter.o

build/code_formatter.o: src/code_formatter.cpp
	-mkdir -p build
	g++ -Wall -std=c++11 -Iinclude -o build/code_formatter.o -c src/code_formatter.cpp
