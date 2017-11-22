default: main.exe
fileReader.o: fileReader.hpp fileReader.cpp
        g++ -c fileReader.cpp
parse.o: parse.hpp parse.cpp
        g++ -c parse.cpp
word.o: word.hpp word.cpp
        g++ -c word.cpp
main.o: main.cpp fileReader.hpp word.hpp parse.hpp
        g++ -c main.cpp
main.exe: main.o fileReader.o word.o parse.o
        g++ main.o fileReader.o word.o parse.o
clean:
        rm -f *.o*

