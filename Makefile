default: main.exe
fileReader.o: fileReader.hpp fileReader.cpp
	g++ -c fileReader.cpp
        
word.o: word.hpp word.cpp
	g++ -c word.cpp
main.o: main.cpp fileReader.hpp word.hpp
	g++ -c main.cpp
main.exe: main.o fileReader.o word.o
	g++ main.o fileReader.o word.o
clean:
	rm -f *.o*

