#include <iostream>
#include <fstream>
#include<vector>
#include<sstream>
#include <string>
#include<map>
#include "hf/labels.hpp"
#include "hf/variables.hpp"
using namespace std;
using namespace GetLabel;
using namespace GetVariables;

vector<string> split(const string& s, char delimiter) {
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}
string getValue(string instruc){
    string value = "";
    for (char c : instruc) {
            if (isdigit(c)) {
                value += c;
            }
        }
    return value;
}
bool linearSearch(vector<string> searchlist, string searchTerm){
    int n =0;
    for (int i=0; i< searchlist.size();i++){
        if(searchlist[i] == searchTerm){
            return true;
        }
    }
    return false;

}
int main(){
    ifstream sourceCode("code.txt");
    string myText;
    vector<string> code = {};
    while (getline(sourceCode, myText)) {code.push_back(myText);}
    if(code.size() >= 100)
    {
         throw invalid_argument( "the source code file needs to 99 lines or less" );
    }
    string line;
    int sizeOfline;
    int index = 0;
    vector<string> splitLine;
    vector<string> dontrequireinput = {"INP", "OUT", "HLT"};
    vector<string> loops = {"BRZ", "BRA", "BRP"};
    map<string, int> mainfunctions = {{"INP",901},{"ADD",100},{"SUB", 200}, {"BRA",600}, {"BRZ", 700}, {"BRP",800}, {"LDA", 700}, {"STA", 300}, {"HLT", 0}, {"OUT", 902}, {"DAT", 0}};
    const int f = code.size();
    vector<vector<string>> lines= {};
    for(int i=0; i<f;i++){
        line = code[i];
        if( !linearSearch(dontrequireinput, line)){
            splitLine = split(line, ' ');
            lines.push_back(splitLine);
        }else{
            lines.push_back(vector<string>{line});
        }
    }
    vector<vector<string>>* ptr = &lines;
    map<string, int> labels = getLabels(ptr, mainfunctions);
    map<string, int> variables = getVariables(ptr, mainfunctions);

    vector<string> memory = {"000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "009", "000", "000", "000", "000"};
    vector<string> c;
    int k;
    const int lineLength = lines.size();
    int val;
    int lastidx;
    string labelname;
    string varname;
    vector<vector<string>>* linesPointer = &lines;
    int it;
    for(int i=0; i<lineLength;i++){
        c = lines[i];
        
        lastidx = c.size()-1;
        if(linearSearch(loops, c[0])){
                if(labels.find(c[lastidx]) != labels.end()){
                    labelname = c[lastidx];
                    it = labels[labelname];
                    (*linesPointer)[i][lastidx] = to_string(it);
                }
                
            }


        if(variables.find(c[lastidx]) != variables.end()){
            varname = c[lastidx];
            it = variables[varname];
            (*linesPointer)[i][lastidx] = to_string(it);
        }
        if(i==17){
            for(string d: lines[i]){cout<<d <<endl;}
        }
        c = lines[i];
        if (mainfunctions.count(c[0])){
            if (linearSearch(dontrequireinput, c[0])){
                if(c[0] == "HLT"){
                    memory[i] = "000";
                }else{
                    memory[i] = to_string(mainfunctions[c[0]]);
                }
            }else{
                if(c[0] == "DAT"){
                    val = stoi(getValue(c[c.size()-1]));
                    if(val < 10){
                        memory[i] = "00"+to_string(mainfunctions[c[0]]+val);
                    }else{
                        memory[i] = "0"+to_string(mainfunctions[c[0]]+val);
                    }
                }else{
                    val = stoi(getValue(c[c.size()-1]));
                    memory[i] = to_string(mainfunctions[c[0]]+val);
                }
            }
        } 
        
    }
    
    const int sizeofmemory = memory.size();
    for(int h=0; h<sizeofmemory; h++){
        cout <<"\"" << memory[h] << "\"" ",";
    }

    
    return 0;
}


