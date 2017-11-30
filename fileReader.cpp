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
#include <vector>
#include <sstream>
#include <iostream>


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
    
    for (int i = 0;logFile >> sampleTemp; i++)    //Stop at line 200 for testing purposes
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
        if (cycleTemp == "Rd")            //Store strings as Read or Write instead of Rd or Wr
        {
            cycleTemp= "Read";
        }
        else
        {
            cycleTemp="Write";
        }
        
        //Ignore th last 4 columns
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        logFile >> trash;
        
        total++;
        
        checkAddress(addressTemp);
        
    }

}

bool fileRead::checkAddress(string a)
{
    long int addressTemp = word::toInt(a) ;
    
    if(addressTemp == 0x40000810)
    {
        rev=false;
        order=0;
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " S-to-D: ");
        
        return true;
    }
    else if(addressTemp >= 0x40000818 && addressTemp <= 0x4000086B)
    {
        order++;
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " S-to-D: ");
        
        return true;
    }
    else if (addressTemp == 0x40000C18)
    {
        rev=false;
        order=0;
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " D-to-S: ");
        
        return true;
    }
    else if (addressTemp >= 0x40000C20 && addressTemp <= 0x40000C73)
    {
        order++;
        parser(addressTemp, dataTemp, sizeTemp, cycleTemp, " D-to-S: ");
        
        return true;
    }
    
    return false;
}

void fileRead::parser(long int addressTemp, string dataTemp, string sizeTemp, string cycleTemp, string t){

    if(order ==1 && (addressTemp == ( 0x40000810 + 8) || (addressTemp == ( 0x40000C18 + 8) )))
        rev = true;

    if ( addressTemp == 0x40000810 || addressTemp == 0x40000c18){
        if ( ! first)
            cout << endl;
        size = word::toInt(dataTemp)/2;
        cout << "line " << total << ": " << cycleTemp << t << size << " words" << endl;
        first = false;

    }


    if (rev)
    {

        string data0 = dataTemp.substr(0,4);
        string data1 = dataTemp.substr(4,7);
        switch (addressTemp){

            case 0x40000818 : cout << "line " << total <<": "; word::word0(data0);cout << "line " << total <<": "; word::word1(data1); break;
            case 0x40000820 : cout << "line " << total <<": "; word::word4(data0);cout << "line " << total <<": " ; word::word5(data1); break;
            case 0x4000082c : cout << "line " << total <<": "; word::word10(data0);break;
            case 0x40000834 : cout << "line " << total <<": "; word::word15(data1);break;
            case 0x40000844 : cout << "line " << total <<": "; word::word22(data0);break;
            case 0x40000858 : cout << "line " << total <<": "; word::word32(data0);break;
            case 0x40000860 : cout << "line " << total <<": "; word::word37(data1);break;
            case 0x40000864 : cout << "line " << total <<": "; word::word38(data0);break;
            case 0x40000868: cout << "line " << total <<": "; word::word40(data0);cout << "line " << total <<": ";word::word41(data1); break;

            case 0x40000c20 : cout << "line " << total <<": "; word::word0(data0);cout << "line " << total <<": "; word::word1(data1); break;
            case 0x40000c28 : cout << "line " << total <<": "; word::word4(data0);cout << "line " << total <<": " ; word::word5(data1); break;
            case 0x40000c34 : cout << "line " << total <<": "; word::word10(data0);break;
            case 0x40000c3c : cout << "line " << total <<": "; word::word15(data1);break;
            case 0x40000c4c : cout << "line " << total <<": "; word::word22(data0);break;
            case 0x40000c60 : cout << "line " << total <<": "; word::word32(data0);break;
            case 0x40000c68 : cout << "line " << total <<": "; word::word37(data1);break;
            case 0x40000c6c : cout << "line " << total <<": "; word::word38(data0);break;
            case 0x40000c70: cout << "line " << total <<": "; word::word40(data0);cout << "line " << total <<": ";word::word41(data1); break;                                    }
    }
    else
    {

        string data0 = dataTemp.substr(0,4);
        string data1 = dataTemp.substr(4,7);
        switch (addressTemp){

            case 0x40000818 : cout << "line " << total <<": "; word::word1(data1);cout << "line " << total <<": "; word::word0(data0); break;
            case 0x40000820 : cout << "line " << total <<": " ; word::word5(data1);cout << "line " << total <<": "; word::word4(data0); break;
            case 0x4000082c : cout << "line " << total <<": "; word::word10(data0);break;
            case 0x40000834 : cout << "line " << total <<": "; word::word15(data1);break;
            case 0x40000844 : cout << "line " << total <<": "; word::word22(data0);break;
            case 0x40000858 : cout << "line " << total <<": "; word::word32(data0);break;
            case 0x40000860 : cout << "line " << total <<": "; word::word37(data1);break;
            case 0x40000864 : cout << "line " << total <<": "; word::word38(data0);break;
            case 0x40000868: cout << "line " << total <<": ";word::word41(data1);cout << "line " << total <<": "; word::word40(data0); break;

            case 0x40000c20 : cout << "line " << total <<": "; word::word1(data1); cout << "line " << total <<": "; word::word0(data0);break;
            case 0x40000c28 : cout << "line " << total <<": " ; word::word5(data1);cout << "line " << total <<": "; word::word4(data0); break;
            case 0x40000c34 : cout << "line " << total <<": "; word::word10(data0);break;
            case 0x40000c3c : cout << "line " << total <<": "; word::word15(data1);break;
            case 0x40000c4c : cout << "line " << total <<": "; word::word22(data0);break;
            case 0x40000c60 : cout << "line " << total <<": "; word::word32(data0);break;
            case 0x40000c68 : cout << "line " << total <<": "; word::word37(data1);break;
            case 0x40000c6c : cout << "line " << total <<": "; word::word38(data0);break;
            case 0x40000c70: cout << "line " << total <<": ";word::word41(data1);cout << "line " << total <<": "; word::word40(data0); break;                                    }
    }
}


