all: 1.out CBC.out

1.out: 1.cpp
	g++ 1.cpp -Wall -std=c++11 -o 1.out
CBC.out: CBC.cpp Functions.o Functions.hpp
	g++ Functions.o CBC.cpp -Wall -std=c++11 -o CBC.out
Functions.o: Functions.cpp Functions.hpp
	g++ Functions.cpp -c -Wall -std=c++11
