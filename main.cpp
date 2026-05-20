#include <iostream>
#include <stdlib.h>
#include <vector>
#include<string>
using namespace std;
int getValue(string instruc){
    string value = "";
    int index =0;
    for (char c : instruc) {
            if (isdigit(c) && index !=0) {
                value += c;
            }index ++;
        }
    return stoi(value);
}
void setValue(vector<string>* mem, int value, int idx){
    string putIn = "0"+to_string(value);
    if (value < 10){
        putIn = "0" +putIn;
    }
    (*mem)[idx] = putIn;
}
int loadIdx(vector<string>* mem, int loadIdx){
    string memVal = (*mem)[loadIdx];
    int value = getValue(memVal);
    return value;
}
int main(){
    vector<string> memory = {"901","314","901","000","716","114","316","715","217","711","803","000","902","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","000","009","000","000","000","000"};
    const int f = memory.size();
    //cout << "test" << endl;
    //cout << f << endl;
    string command = "001";
    int progam_counter = 0;
    int accumulator = 0;
    string instruction = "001";
    bool flag = false;
    do {
        flag = false;
        instruction = memory[progam_counter];
        //cout << instruction << endl;
        if (instruction[0] == '9' && instruction[instruction.length() - 1]== '1'){ cin >> accumulator;}
        if (instruction[0] == '9' && instruction[instruction.length() - 1]== '2'){ cout << accumulator << endl;}
        if (instruction[0] == '1'){
            int getIdx = getValue(instruction);
            accumulator = accumulator + getValue(memory[getIdx]);
        } // add
        if (instruction[0] == '2'){
           int getIdx = getValue(instruction);
            accumulator = getValue(memory[getIdx]) -accumulator;
        } // subtract
        if (instruction[0] == '3'){int placeIdx = getValue(instruction);
            vector<string>* ptr = &memory;
            setValue(ptr, accumulator, placeIdx);
            //cout << "this is the value of the STA command: "<< memory[placeIdx] << endl;
        } // store value at xx
        if (instruction[0] == '5'){
            vector<string>* ptr = &memory;
            int getIdx = getValue(instruction);
            accumulator = loadIdx(ptr, getIdx);
        }// LDA
        if (instruction[0] == '6'){
            progam_counter = getValue(instruction);
            flag = true;
        }//BRA
        if (instruction[0] == '7'){if (accumulator==0){progam_counter = getValue(instruction);flag=true;}}//BRZ
        if (instruction[0] == '8'){if (accumulator>0){progam_counter = getValue(instruction);flag=true;}} //BRP
        
        if (!flag){
            progam_counter ++;
        }
       



    }while (instruction != "000");
    
    
}