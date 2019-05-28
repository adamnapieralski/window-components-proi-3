all: proi3

proi3: proi3.o wincomponents.o shell.o
	g++ -std=c++11 -g -o proi3 proi3.o wincomponents.o shell.o
	rm *.o

proi3.o: proi3.cpp
	g++ -std=c++11 -g -c proi3.cpp

chess.o: wincomponents.cpp
	g++ -std=c++11 -g -c wincomponents.cpp

shell.o: shell.cpp
	g++ -std=c++11 -g -c shell.cpp

clean:
	rm *0 proi3 *.o
