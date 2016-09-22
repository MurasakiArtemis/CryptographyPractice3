all: Main.out

1.out: 1.cpp
	g++ 1.cpp -Wall -std=c++11 -o 1.out
Main.out: Main.cpp Functions.o Functions.hpp
	g++ Functions.o Main.cpp -Wall -std=c++11 -o Main.out
Functions.o: Functions.cpp Functions.hpp
	g++ Functions.cpp -c -Wall -std=c++11
