default: main.exe
fileReader.o: fileReader.hpp fileReader.cpp
	g++ -std=c++11 -c fileReader.cpp
        
word.o: word.hpp word.cpp
	g++ -std=c++11 -c word.cpp
main.o: main.cpp fileReader.hpp word.hpp
	g++ -std=c++11 -c main.cpp
main.exe: main.o fileReader.o word.o
	g++ -std=c++11 main.o fileReader.o word.o
clean:
	rm -f *.o*

