//
//  fileReader.cpp
//  project
//
//  Created by Enrique Mendoza on 11/16/17.
//  Copyright © 2017 Enrique Mendoza. All rights reserved.
//

#include "fileReader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

fileRead::fileRead(string filename)
{
    string sampleTemp;
    string relTimeTemp;
    long int addressTemp;
    string dataTemp;
    string sizeTemp;
    string cycleTemp;
    int line = 0;
    string trash;       // Ignore unneccssary columns
    
    ifstream logFile;
    logFile.open(filename);
    
    //Read in the colunm names and ignore them
    for(int i = 0; i <14; i++)
        logFile >> trash;
    
    while (logFile >> sampleTemp)
    {
        Sample.push_back(sampleTemp);
        logFile >> trash;               //Ignore Bgl column
        logFile >> relTimeTemp;
        RelTime.push_back(relTimeTemp);
        
        //Ignore AbsTime, Transfer and AM/XAM columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        //Get address column and save as hex value
        logFile >> hex >> addressTemp;
        Address.push_back(addressTemp);
        //Get data column and save as hex value
        logFile >> dataTemp;
        Data.push_back(dataTemp);
        //Get size and data coumn
        logFile >> sizeTemp;
        Size.push_back(sizeTemp);
        logFile >> cycleTemp;
        Cycle.push_back(cycleTemp);
        lineNumber.push_back(++line);
        
        //Ignore th last 4 columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        total++;
    }
}

//int fileRead::getLineNumber() const { return lineNumber; }
long int fileRead::getTotal() const { return total; }
