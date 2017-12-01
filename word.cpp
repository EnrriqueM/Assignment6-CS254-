//  CSUF CPSC 254, Fall 2017 Assignment 6
//
// Team Members:
// Walid El Mir
// David Williams-Haven
// Dat Nguyen
// Enrique Mendoza
//
// Filename: word.cpp
//
// This class has 12 functions, each is specified to parse one of the 12 different words we dealing with in each command

#include "word.hpp"

// convert string to hex integer 
long int word::toInt(string pars){
    long int word;
    istringstream buffer(pars);
    buffer >> hex >> word;
    return word;
}

void word::word0(string word){
    
    long int word0 = toInt(word);
    
    word0 = word0 & 0x6000;
    word0 = word0 >> 13;
    
    if ( word0 == 0)
        cout << "Word 0: Rec_Ctrl = " << word0 <<" (no recording)" << endl;
    else if (word0 == 2)
        cout << "Word 0: Rec_Ctrl = " << word0 <<" (no processing)" << endl;
    else if (word0 == 3)
        cout << "Word 0: Rec_Ctrl = " << word0 <<" (processing & recording)" << endl;
}

void word::word1(string word){
    
    long int word1 = toInt(word);
    
    word1 = word1 & 0xe000;
    word1 = word1 >> 13;
    
    if ( word1 == 4)
        cout << "Word 1: Cmd_type = " << word1 <<" (type A)" << endl;
    else if (word1 == 5)
        cout << "Word 1: Cmd_type = " << word1 <<" (type B)" << endl;
    else if (word1 == 6)
        cout << "Word 1: Cmd_type = " << word1 <<" (typre C)" << endl;
    else cout << "Word 1: Cmd_type = " << word1 <<" (unknown)" << endl;
}

void word::word4(string word){
    
    long int word4 = toInt(word);
    
    word4 = word4 & 0x0001;
    
    if ( word4 == 0)
        cout << "Word 4: Rec_Raw = " << word4 <<" (disable)" << endl;
    else if (word4 == 1)
        cout << "Word 4: Rec_Raw = " << word4 <<" (enable)" << endl;
}

void word::word5(string word){
    
    long int word5 = toInt(word);
    
    word5 = word5 & 0x001f;
    cout << "Word 5: Cmd_ID = " << word5 << endl;
}

void word::word10(string word){
    
    long int word10 = toInt(word);
    
    word10 = word10 >> 11;
    cout << "Word 10: Num_Responses = " << word10 << endl;
}

void word::word15(string word){
    
    long int word15 = toInt(word);
    
    word15 = word15 & 0x0004;
    word15 = word15 >> 2;
    
    if ( word15 == 0)
        cout << "Word 15: Reset_Enable = " << word15 <<" (disable)" << endl;
    else if (word15 == 1)
        cout << "Word 15: Reset_Enable = " << word15 <<" (enable)" << endl;
}

void word::word22(string word){
    
    long int word22 = toInt(word);
    
    word22 = word22 & 0x0008;
    word22 = word22 >> 3;
    
    if ( word22 == 0)
        cout << "Word 22: Direction = " << word22 <<" (Right)" << endl;
    else if (word22 == 1)
        cout << "Word 22: Direction = " << word22 <<" (Left)" << endl;
}

void word::word32(string word){
    
    long int word32 = toInt(word);
    
    word32 = word32 & 0x7fff;
    cout << "Word 32: Num_Samples = " << word32 << endl;
}

void word::word37(string word){
    
    long int word37 = toInt(word);
    
    word37 = word37 >> 15;
    
    if ( word37 == 0)
        cout << "Word 37: Parity = " << word37 <<" (even)" << endl;
    else if (word37 == 1)
        cout << "Word 37: Parity = " << word37 <<" (odd)" << endl;
}

void word::word38(string word){
    
    long int word38 = toInt(word);
    
    word38 = word38 & 0x4000;
    word38 = word38 >> 14;
    
    if ( word38 == 0)
        cout << "Word 38: Test = " << word38 <<" (disable)" << endl;
    else if (word38 == 1)
        cout << "Word 38: Test = " << word38 <<" (enable)" << endl;
}

void word::word40(string word){
    
    long int word40 = toInt(word);
    
    word40 = word40 & 0x0008;
    word40 = word40 >> 7;
    
    if ( word40 == 0)
        cout << "Word 40: Ctrl_Enable = " << word40 <<" (disable)" << endl;
    else if (word40 == 1)
        cout << "Word 40: Ctrl_Enable = " << word40 <<" (enable)" << endl;
}

void word::word41(string word){
    
    long int word41 = toInt(word);
    
    word41 = word41 & 0x7ff0;
    word41 = word41 >> 8;
    
    cout << "Word 41: Code = " << word41 << endl;
}
