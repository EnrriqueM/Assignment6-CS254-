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
    vector<string> getSample();
	vector<string> getRelTime();
	vector<long int> getAddress();
	vector<string> getData();
	vector<string> getSize();
	vector<string> getCycle();
	vector<string> getType();
	vector<long int> getlineNumber();
	long int getTotal() const;
    
private:
    //Vectors work in parallel
    vector<string> Sample;          //Holds Sample column
    vector<string> RelTime;         //RelTime column
    vector<long int> Address;         //Address column
    vector<string> Data;            //Data column
    vector<string> Size;            //Size column
    vector<string> Cycle;           //Cycle Column
    vector<string> Type;			//D-to-S or S-to-D
    vector<long int> lineNumber;    //Line number each row appeared
    long int total = 1;             //Total things red
    bool checkAddress(string);      //Check if we need this address stored
};

#endif /* fileReader_hpp */
