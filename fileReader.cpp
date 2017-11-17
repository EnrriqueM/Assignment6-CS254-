//  CSUF CPSC 254, Fall 2017 Assignment 6
//
// Team Members:
// David Williams-Haven
// Dat Nguyen
// Enrique Mendoza
// Walid El Mir
//
// Filename: fileReader.cpp

#include "fileReader.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>

//Constructor
//Read in from files
fileRead::fileRead(string filename)
{
    //Temporary values
    string sampleTemp;
    string relTimeTemp;
    string addressTemp;
    string dataTemp;
    string sizeTemp;
    string cycleTemp;
    string trash;       // Ignore unneccssary columns
    
    ifstream logFile;
    logFile.open(filename);
    
    //Read in the colunm names and ignore them
    for(int i = 0; i <14; i++)
        logFile >> trash;
    
    while (logFile >> sampleTemp)
    {
        bool found = false;
        
        logFile >> trash;               //Ignore Bgl column
        logFile >> relTimeTemp;         //Retrieve RelTime col.
        
        //Ignore AbsTime, Transfer and AM/XAM columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        //Get address column and save as hex value
        logFile >> hex >> addressTemp;
        //Get data column
        //NOTE: Stored as string as hex value too big
        logFile >> dataTemp;
        //Get size and data coumn
        logFile >> sizeTemp;
        logFile >> cycleTemp;
        
        //Ignore th last 4 columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        total++;
        
        found = checkAddress(addressTemp);
        
        //If matches address, add values to appriprate vectors
        if(found)
        {
            Sample.push_back(sampleTemp);
            RelTime.push_back(relTimeTemp);
            Data.push_back(dataTemp);
            Size.push_back(sizeTemp);
            Cycle.push_back(cycleTemp);
            lineNumber.push_back(total);
        }
    }
    
    //Close file
    logFile.close();
}

//int fileRead::getLineNumber() const { return lineNumber; }
long int fileRead::getTotal() const { return total; }

//Private Function:
//Adds wanted address to vector
bool fileRead::checkAddress(string a)
{
    long int addressTemp;
    istringstream buffer(a);        //Converts strings to ints
    
    //Try to convert address into a hex value
    buffer >> hex >> addressTemp;
    
    //Only add wanted addresses to vector
    if(addressTemp == 0x40000810 || (addressTemp >= 0x40000818 && addressTemp <= 0x40000C14) ||
       addressTemp == 0x40000C18 || (addressTemp >= 0x40000C20 && addressTemp <= 0x4000101C))
    {
        Address.push_back(addressTemp);
        return true;
    }
    
    return false;
}



