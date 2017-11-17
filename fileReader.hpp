//
//  fileReader.hpp
//  project
//
//  Created by Enrique Mendoza on 11/16/17.
//  Copyright © 2017 Enrique Mendoza. All rights reserved.
//

#ifndef fileReader_hpp
#define fileReader_hpp

#include <string>
#include <vector>

#include <stdio.h>

using namespace std;

class fileRead{
public:
    fileRead(string);                   // Constructor
    int getLineNumber() const;          // Returns total number of lines red
    long int getTotal() const;
    
//private:
    //Vectors work in parallel
    vector<string> Sample;         //Holds Sample column
    vector<string> RelTime;        //RelTime column
    vector<long int> Address;        //Address column
    vector<string> Data;           //Data column
    vector<string> Size;        //Size column
    vector<string> Cycle;       //Cycle Column
    vector<int> lineNumber;     //Line number each row appeared
    long int total = 0;              //Total things red
};

#endif /* fileReader_hpp */
