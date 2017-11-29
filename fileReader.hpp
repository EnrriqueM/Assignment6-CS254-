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
    
	long int getTotal() const;
    
    void parser(long int, string, string ,string , string);
    bool checkAddress(string);      //Check if we need this address
   long int total = 1;
};

#endif /* fileReader_hpp */
