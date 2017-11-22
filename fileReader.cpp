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
#include <iostream>

using namespace std;

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
    string typeTemp;
    string trash;       // Ignore unneccssary columns
    
    ifstream logFile;
    logFile.open(filename);

    
    //Read in the colunm names and ignore them
    for(int i = 0; i <14; i++)
        logFile >> trash;
	bool wasFound = false;
	bool found = false;
    for (int i = 0;logFile >> sampleTemp && i < 200; i++)	//Stop at line 200 for testing purposes
    {
		//cout << i << endl;
		if (found == true)
		{
			wasFound = true;
		}
		else
		{
			wasFound = false;
		}
        found = false;
        logFile >> trash;               //Ignore Bgl column
        logFile >> relTimeTemp;         //Retrieve RelTime col.
        if (wasFound)					//Check if the address was found in the previous row and assign the time
		{
			RelTime.push_back(relTimeTemp);
			//cout << "Time: " << relTimeTemp << endl;
		}
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
            Data.push_back(dataTemp);
            Size.push_back(sizeTemp);
            if (cycleTemp == "Rd")			//Store strings as Read or Write instead of Rd or Wr
            {
				Cycle.push_back("Read");
            }
            else
            {
				Cycle.push_back("Write");
			}
            lineNumber.push_back(total);
			wasFound = true;
        }
    }
    
    //Close file
    logFile.close();
}

//int fileRead::getLineNumber() const { return lineNumber; }
long int fileRead::getTotal() const { return total; }

vector<string> fileRead::getSample() { return Sample; }

vector<string> fileRead::getRelTime() { return RelTime; }

vector<string> fileRead::getData() { return Data; }

vector<string> fileRead::getSize() { return Size; }

vector<string> fileRead::getCycle() { return Cycle; }

vector<string> fileRead::getType() { return Type; }

vector<long int> fileRead::getlineNumber() { return lineNumber; }

vector<long int> fileRead::getAddress() { return Address;}


//Private Function:
//Adds wanted address to vector
bool fileRead::checkAddress(string a)
{
    long int addressTemp;
    istringstream buffer(a);        //Converts strings to ints

    //Converts address to decimal
    buffer >> hex >> addressTemp;
    
    //Only add wanted addresses to vector
    if(addressTemp == 0x40000810 || (addressTemp >= 0x40000818 && addressTemp <= 0x4000086B))
    {
        Address.push_back(addressTemp);
        //cout << endl << a << endl;
        Type.push_back(" S-to-D: ");
        return true;
    }
    else if (addressTemp == 0x40000C18 || (addressTemp >= 0x40000C20 && addressTemp <= 0x40000C73))
    {
		Address.push_back(addressTemp);
		Type.push_back(" D-to-S: ");
        return true;
	}
    
    return false;
}
