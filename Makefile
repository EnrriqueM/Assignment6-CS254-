default: main.exe
fileReader.o: fileReader.hpp fileReader.cpp
	g++ -c fileReader.cpp
main.o: main.cpp fileReader.hpp
	g++ -c main.cpp
main.exe: main.o fileReader.o
	g++ main.o fileReader.o
	
clean:
	rm -f *.o*

