lab7: main.o
	g++ -std=c++11 -g -Wall main.o -o lab7

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

clean:
	rm *.o lab7
