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
#include "word.hpp"


#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <iostream>
#include <iomanip>


using namespace std;

//Constructor
//Read in from files
fileRead::fileRead(string filename)
{
    string trash;       // Ignore unneccssary columns
    
    ifstream logFile;
    logFile.open(filename);
    //Read in the colunm names and ignore them
    for(int i = 0; i <14; i++)
        logFile >> trash;
    bool found = false;
    for (int i = 0;logFile >> sampleTemp; i++)
    //for (int i = 0;logFile >> sampleTemp && i < 200; i++)    //Stop at line 200 for testing purposes
    {
        logFile >> trash;               //Ignore Bgl column
        logFile >> relTimeTemp;         //Retrieve RelTime col.
        
        //Ignore AbsTime, Transfer and AM/XAM columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        //Get address column and save as hex value
        logFile >> hex >> addressTemp;
        
        //Get data column
        logFile >> dataTemp;
        //Get size and data coumn
        logFile >> sizeTemp;
        logFile >> cycleTemp;
        if (found)
        {
			addTime(convertTime(relTimeTemp));
		}
        
        if (cycleTemp == "Rd")            //Store strings as Read or Write instead of Rd or Wr
        {
            cycleTemp = "Read";
        }
        else
        {
            cycleTemp = "Write";
        }
        
        //Ignore th last 4 columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        total++;
        
        if (checkAddress(addressTemp))
        {
			found = true;
			lastCycle = cycleTemp;
			lastType = typeTemp;
			addSize(convertSize(sizeTemp));
		}
		else
		{
			found = false;
        }

	}
	for (int i = 0; i < 4; i++)
	{
		dataRate[i] += (totalSize[i] / totalTime[i]);
		dataRate[i] *= pow(10,-6);
	}
	cout << fixed << setprecision(2) << "\n\nRead S-to-D: " << dataRate[0] << " Megabits/s\n";
	cout << fixed << setprecision(2) << "Read D-to-S: " << dataRate[1] << " Megabits/s\n";
	cout << fixed << setprecision(2) << "Write S-to-D: " << dataRate[2] << " Megabits/s\n";
	cout << fixed << setprecision(2) << "Write D-to-S: " << dataRate[3] << " Megabits/s\n";

}

bool fileRead::checkAddress(string a)
{
    long int addressTemp = word::toInt(a) ;
    
    if(addressTemp == 0x40000810)
    {
        rev=false;//for order use
        order=0;//for order use
        typeTemp = "SD";
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " S-to-D: ");
        
        return true;
    }
    else if(addressTemp >= 0x40000818 && addressTemp <= 0x4000086B)
    {
        order++;//for order use
        typeTemp = "SD";
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " S-to-D: ");
        return true;
    }
    else if (addressTemp == 0x40000C18)
    {
        rev=false;//for order use
        order=0;//for order use
        typeTemp = "DS";
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " D-to-S: ");
        
        return true;
    }
    else if (addressTemp >= 0x40000C20 && addressTemp <= 0x40000C73)
    {
        order++;//for order use
        typeTemp = "DS";
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " D-to-S: ");
        
        return true;
    }
    
    return false;
}

void fileRead::parser(long int addressTemp, string dataTemp, string sizeTemp, string cycleTemp, string t){

    if(order ==1 && (addressTemp == ( 0x40000810 + 8) || (addressTemp == ( 0x40000C18 + 8) )))// to determine the order 
        rev = true;

    if ( addressTemp == 0x40000810 || addressTemp == 0x40000c18){
        if ( ! first)//check if it is the new command 
            cout << endl;
        size = word::toInt(dataTemp)/2;
        cout << "Line " << total << ": " << cycleTemp << t << size << " words" << endl;//command head
        first = false;

    }


    else if (rev)// parse in acending order 
    {

        string data0 = dataTemp.substr(0,4);
        string data1 = dataTemp.substr(4,7);
        switch (addressTemp){

            case 0x40000818 : cout << "Line " << total <<": "; word::word0(data0);cout << "Line " << total <<": "; word::word1(data1); break;
            case 0x40000820 : cout << "Line " << total <<": "; word::word4(data0);cout << "Line " << total <<": " ; word::word5(data1); break;
            case 0x4000082c : cout << "Line " << total <<": "; word::word10(data0);break;
            case 0x40000834 : cout << "Line " << total <<": "; word::word15(data1);break;
            case 0x40000844 : cout << "Line " << total <<": "; word::word22(data0);break;
            case 0x40000858 : cout << "Line " << total <<": "; word::word32(data0);break;
            case 0x40000860 : cout << "Line " << total <<": "; word::word37(data1);break;
            case 0x40000864 : cout << "Line " << total <<": "; word::word38(data0);break;
            case 0x40000868: cout << "Line " << total <<": "; word::word40(data0);cout << "Line " << total <<": ";word::word41(data1); break;

            case 0x40000c20 : cout << "Line " << total <<": "; word::word0(data0);cout << "Line " << total <<": "; word::word1(data1); break;
            case 0x40000c28 : cout << "Line " << total <<": "; word::word4(data0);cout << "Line " << total <<": " ; word::word5(data1); break;
            case 0x40000c34 : cout << "Line " << total <<": "; word::word10(data0);break;
            case 0x40000c3c : cout << "Line " << total <<": "; word::word15(data1);break;
            case 0x40000c4c : cout << "Line " << total <<": "; word::word22(data0);break;
            case 0x40000c60 : cout << "Line " << total <<": "; word::word32(data0);break;
            case 0x40000c68 : cout << "Line " << total <<": "; word::word37(data1);break;
            case 0x40000c6c : cout << "Line " << total <<": "; word::word38(data0);break;
            case 0x40000c70: cout << "Line " << total <<": "; word::word40(data0);cout << "Line " << total <<": ";word::word41(data1); break;                                    }
    }
    else//parse in decending order 
    {

        string data0 = dataTemp.substr(0,4);
        string data1 = dataTemp.substr(4,7);
        switch (addressTemp){

            case 0x40000818 : cout << "Line " << total <<": "; word::word1(data1);cout << "Line " << total <<": "; word::word0(data0); break;
            case 0x40000820 : cout << "Line " << total <<": " ; word::word5(data1);cout << "Line " << total <<": "; word::word4(data0); break;
            case 0x4000082c : cout << "Line " << total <<": "; word::word10(data0);break;
            case 0x40000834 : cout << "Line " << total <<": "; word::word15(data1);break;
            case 0x40000844 : cout << "Line " << total <<": "; word::word22(data0);break;
            case 0x40000858 : cout << "Line " << total <<": "; word::word32(data0);break;
            case 0x40000860 : cout << "Line " << total <<": "; word::word37(data1);break;
            case 0x40000864 : cout << "Line " << total <<": "; word::word38(data0);break;
            case 0x40000868: cout << "Line " << total <<": ";word::word41(data1);cout << "Line " << total <<": "; word::word40(data0); break;

            case 0x40000c20 : cout << "Line " << total <<": "; word::word1(data1); cout << "Line " << total <<": "; word::word0(data0);break;
            case 0x40000c28 : cout << "Line " << total <<": " ; word::word5(data1);cout << "Line " << total <<": "; word::word4(data0); break;
            case 0x40000c34 : cout << "Line " << total <<": "; word::word10(data0);break;
            case 0x40000c3c : cout << "Line " << total <<": "; word::word15(data1);break;
            case 0x40000c4c : cout << "Line " << total <<": "; word::word22(data0);break;
            case 0x40000c60 : cout << "Line " << total <<": "; word::word32(data0);break;
            case 0x40000c68 : cout << "Line " << total <<": "; word::word37(data1);break;
            case 0x40000c6c : cout << "Line " << total <<": "; word::word38(data0);break;
            case 0x40000c70: cout << "Line " << total <<": ";word::word41(data1);cout << "Line " << total <<": "; word::word40(data0); break;                                    }
    }
}

double fileRead::convertTime(string timeString)
{
	string timeTemp = timeString;
	timeTemp.pop_back();
	timeTemp.pop_back();
	double timeDouble = stod(timeTemp);				//Delete the units and convert string to double for arithmetic
	
	int secondLastChar = relTimeTemp.length()-2;	//Check if the unit is nano micro or milli
	
	if (timeString[secondLastChar] == 'n')
	{
		timeDouble *= pow(10,-9);
	}
	else if (timeString[secondLastChar] == 'u')
	{
		timeDouble *= pow(10,-6);
	}
	else if (timeString[secondLastChar] == 'm')
	{
		timeDouble *= pow(10,-3);
	}
	//cout << "Line: "<< i+1 << " Time: " << timeDouble << "s\n\n";
	return timeDouble;
}

double fileRead::convertSize(string sizeString)
{
	sizeString.erase(0,1);
	double size = stod(sizeString);
	return size;
}

void fileRead::addTime(double time)
{
	int index;
	if (lastCycle == "Read" && lastType == "SD")
	{
		index = 0;
	}
	else if (lastCycle == "Read" && lastType == "DS")
	{
		index = 1;
	}
	else if (lastCycle == "Write" && lastType == "SD")
	{
		index = 2;
	}
	else if (lastCycle == "Write" && lastType == "DS")
	{
		index = 3;
	}
	//cout << "Time Index: " << index << endl;
	totalTime[index] += time;
}
void fileRead::addSize(double size)
{
	
	int index;
	if (cycleTemp == "Read" && typeTemp == "SD")
	{
		index = 0;
	}
	else if (cycleTemp == "Read" && typeTemp == "DS")
	{
		index = 1;
	}
	else if (cycleTemp == "Write" && typeTemp == "SD")
	{
		index = 2;
	}
	else if (cycleTemp == "Write" && typeTemp == "DS")
	{
		index = 3;
	}
	//cout << "Size Index: " << index << endl;
	totalSize[index] += size;
}
