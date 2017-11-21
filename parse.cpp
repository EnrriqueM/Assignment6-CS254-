//
//  parse.cpp
//  logFile
//
//  Created by Walid El Mir on 11/20/17.
//  Copyright © 2017 Walid El Mir. All rights reserved.
//

#include "parse.hpp"
#include "word.hpp"
parse::parse(fileRead file){
    int i =0;
    while(i<file.getSample().size()){
    
        long int address =  file.getAddress()[i];
        long int line = file.getlineNumber()[i];
        long int size = word::toInt(file.getData()[i]);
        
        string cycle = file.getCycle()[i];
        if (cycle == "Wr")
            cycle = "Write";
        else cycle = "Read";
        
        size = size / 2;
        if (address == 0x40000810)
            cout << "line " << line << ": " << cycle << " S-to-D command: " << size << " words" << endl;
        else if(address == 0x40000c18)
            cout << "line " << line << ": " << cycle << " D-to-S command: " << size << " words" << endl;
        
        if ( address == 0x40000810 || address == 0x40000c18){
    
            if (size != 0 && ( file.getAddress()[i+1] == 0x40000818 || file.getAddress()[i+1]==0x40000C20)){
                size = size /2 ;
                int f=0;
                for (int j=i+1 ; j<= i+size; j++){
                    
                    line =  file.getlineNumber()[j];
                    string data0 = file.getData()[j].substr(0,4);
                    string data1 = file.getData()[j].substr(4,7);
                    
                    switch (f){
                            
                        case 0 : cout << "line " << line <<": "; word::word0(data0);cout << "line " << line <<": "; word::word1(data1); break;
                        case 2 : cout << "line " << line <<": "; word::word4(data0);cout << "line " << line <<": " ; word::word5(data1); break;
                        case 5 : cout << "line " << line <<": "; word::word10(data0);break;
                        case 7 : cout << "line " << line <<": "; word::word15(data1);break;
                        case 11 : cout << "line " << line <<": "; word::word22(data0);break;
                        case 16 : cout << "line " << line <<": "; word::word32(data0);break;
                        case 18 : cout << "line " << line <<": "; word::word37(data1);break;
                        case 19 : cout << "line " << line <<": "; word::word38(data0);break;
                        case 20: cout << "line " << line <<": "; word::word40(data0);cout << "line " << line <<": ";word::word41(data1); break;
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
                            
                        case 0 : cout << "line " << line <<": "; word::word1(data1);cout << "line " << line <<": "; word::word0(data0); break;
                        case 2 : cout << "line " << line <<": " ; word::word5(data1);cout << "line " << line <<": "; word::word4(data0); break;
                        case 5 : cout << "line " << line <<": "; word::word10(data0);break;
                        case 7 : cout << "line " << line <<": "; word::word15(data1);break;
                        case 11 : cout << "line " << line <<": "; word::word22(data0);break;
                        case 16 : cout << "line " << line <<": "; word::word32(data0);break;
                        case 18 : cout << "line " << line <<": "; word::word37(data1);break;
                        case 19 : cout << "line " << line <<": "; word::word38(data0);break;
                        case 20: cout << "line " << line <<": ";word::word41(data1); cout << "line " << line <<": "; word::word40(data0); break;
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
