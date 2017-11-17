//
//  main.cpp
//  project
//
//  Created by Enrique Mendoza on 11/16/17.
//  Copyright © 2017 Enrique Mendoza. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

#include "fileReader.hpp"

using namespace std;

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
    
    cout << log1.Sample[log1.getTotal() - 1] << endl;
    cout << log1.getTotal() << endl;
    
    return 0;
}
