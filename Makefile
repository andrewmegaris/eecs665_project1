CXXFLAGS=-g -std=c++11 -Wall -pedantic

output: main.o
	g++ main.o -o project1

main.o: main.cpp
	g++ -c main.cpp


clean:
	rm *.o project1
