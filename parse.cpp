//  CSUF CPSC 254, Fall 2017 Assignment 6
//
// Walid El Mir
// Team Members:
// David Williams-Haven
// Dat Nguyen
// Enrique Mendoza

#include "parse.hpp"
#include "word.hpp"
parse::parse(fileRead file){
    int i =0;
    while(i<file.getSample().size()){
    
        long int address =  file.getAddress()[i];
        long int line = file.getlineNumber()[i];
        long int size = word::toInt(file.getData()[i]);
        
        size = size / 2;
 
        if ( address == 0x40000810 || address == 0x40000c18){
            cout << "Line " << line << ": " << file.getCycle()[i] << file.getType()[i] << size << " words" << endl;
            if (size != 0 && ( file.getAddress()[i+1] == 0x40000818 || file.getAddress()[i+1]==0x40000C20)){
                size = size /2 ;
                int f=0;
                for (int j=i+1 ; j<= i+size; j++){
                    
                    line =  file.getlineNumber()[j];
                    string data0 = file.getData()[j].substr(0,4);
                    string data1 = file.getData()[j].substr(4,7);
                    
                    switch (f){
                            
                        case 0 : cout << "Line " << line <<": "; word::word0(data0);cout << "Line " << line <<": "; word::word1(data1); break;
                        case 2 : cout << "Line " << line <<": "; word::word4(data0);cout << "Line " << line <<": " ; word::word5(data1); break;
                        case 5 : cout << "Line " << line <<": "; word::word10(data0);break;
                        case 7 : cout << "Line " << line <<": "; word::word15(data1);break;
                        case 11 : cout << "Line " << line <<": "; word::word22(data0);break;
                        case 16 : cout << "Line " << line <<": "; word::word32(data0);break;
                        case 18 : cout << "Line " << line <<": "; word::word37(data1);break;
                        case 19 : cout << "Line " << line <<": "; word::word38(data0);break;
                        case 20: cout << "Line " << line <<": "; word::word40(data0);cout << "Line " << line <<": ";word::word41(data1); break;
                    }
                    f++;
                }
                i=i+size;
            }
            
            else if (size != 0 && ( file.getAddress()[i+1] != 0x40000818 && file.getAddress()[i+1]!=0x40000C20)){
                size = size /2 ;
                int f=size-1;
                for (int k=i+1  ; k<= i+size; k++){
                    
                    line =  file.getlineNumber()[k];
                    string data0 = file.getData()[k].substr(0,4);
                    string data1 = file.getData()[k].substr(4,7);
                    
                    switch (f){
                            
                        case 0 : cout << "Line " << line <<": "; word::word1(data1);cout << "Line " << line <<": "; word::word0(data0); break;
                        case 2 : cout << "Line " << line <<": " ; word::word5(data1);cout << "Line " << line <<": "; word::word4(data0); break;
                        case 5 : cout << "Line " << line <<": "; word::word10(data0);break;
                        case 7 : cout << "Line " << line <<": "; word::word15(data1);break;
                        case 11 : cout << "Line " << line <<": "; word::word22(data0);break;
                        case 16 : cout << "Line " << line <<": "; word::word32(data0);break;
                        case 18 : cout << "Line " << line <<": "; word::word37(data1);break;
                        case 19 : cout << "Line " << line <<": "; word::word38(data0);break;
                        case 20: cout << "Line " << line <<": ";word::word41(data1); cout << "Line " << line <<": "; word::word40(data0); break;
                    }
                    f--;
                }
                i=i+size;
            }
            
            
            cout << endl;
        
        }
       i++;
    
    }
};
