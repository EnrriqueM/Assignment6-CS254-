//  CSUF CPSC 254, Fall 2017 Assignment 6
//
// Team Members:
// David Williams-Haven
// Dat Nguyen
// Enrique Mendoza
// Walid El Mir
//
// Filename: fileReader.hpp

#ifndef fileReader_hpp
#define fileReader_hpp

#include <string>
#include <vector>

#include <stdio.h>

using namespace std;

class fileRead{
      
public:
    fileRead(string);                   // Constructor
    
private:
    //Temporary values
	string lineTemp;
	string sampleTemp;
	string relTimeTemp;
	string addressTemp;
	string dataTemp;
	string sizeTemp;
	string cycleTemp;
	string lastCycle;					//Stores Cycle and Type of the previous line
	string typeTemp;
	string lastType;
	int totalSize[4] = {0};				//Indexes: [0] is Read S to D; [1] is Read D to S
	double totalTime[4] = {0};			//Indexes:[2] is Write S to D; [3] is Write D to S
	double dataRate[4] = {0};
	bool first = true;
	int order=0;
	long int size;
	bool rev ;
	
	void parser(long int, string, string ,string , string);
    bool checkAddress(string);      //Check if we need this address
    double convertTime(string);		//Converts size and time from data, to doubles for arithmetic
    double convertSize(string);
    void addTime(double);
    void addSize(double);
	long int total = 1;
};

#endif /* fileReader_hpp */
