default: main.exe
fileReader.o: fileReader.hpp fileReader.cpp
	g++ -std=c++11 -c fileReader.cpp
parse.o: parse.hpp parse.cpp
	g++ -std=c++11 -c parse.cpp
word.o: word.hpp word.cpp
	g++ -std=c++11 -c word.cpp
main.o: main.cpp fileReader.hpp word.hpp parse.hpp
	g++ -std=c++11 -c main.cpp
main.exe: main.o fileReader.o word.o parse.o
	g++ -std=c++11 main.o fileReader.o word.o parse.o
clean:
	rm -f *.o*

