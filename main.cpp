//  CSUF CPSC 254, Fall 2017 Assignment 6
//
// Team Members:
// David Williams-Haven
// Dat Nguyen
// Enrique Mendoza
// Walid El Mir
//
// Filename: main.cpp

#include <iostream>
#include <string>
#include <fstream>

#include "fileReader.hpp"
#include "word.hpp"
#include "output.cpp"

using namespace std;

void output(fileRead);	//Write output

int main(int argc, const char* argu[])
{
    string filename;            //Holds filename
    
    //Check if an argument has been passed
    if (argc < 2)
    {
        cout << "Missing Filename" << endl;
        return 1;
    }
    
    //Check if file opens
    ifstream fin(argu[1]);
    if (!fin)
    {
        cout << "File not found" << endl;
        return 1;
    }
    fin.close();
    
    //Save source file
    filename = argu[1];
    fileRead log1(filename);
    
    //cout << log1.Sample[log1.getTotal() - 1] << endl;
    //cout << log1.getTotal() << endl;
    
	output(log1);
    
    
    // Test parsing
    word w;
    w.word0("0x8255");
    w.word1("0xc405");
    w.word4("0x4000");
    w.word5("0x0008");
    w.word10("0x2c6d");
    w.word15("0x0000");
    w.word22("0x0005");
    w.word32("0x1290");
    w.word37("0x0022");
    w.word38("0x0f33");
    w.word40("0x0600");
    w.word41("0x0801");
    
    return 0;
}
