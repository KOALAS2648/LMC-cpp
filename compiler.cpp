#include <iostream>
#include <fstream>
#include<vector>
#include<sstream>
#include <string>
#include<map>
using namespace std;

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
    while (getline(sourceCode, myText)) {
    // Output the text from the file
    //cout << myText << endl;
    code.push_back(myText);
    
    }
    string line;
    int sizeOfline;
    int index = 0;
    vector<string> splitLine;
    vector<string> dontrequireinput = {"INP", "OUT", "HLT"};
    map<string, int> mainfunctions = {{"INP",901},{"ADD",100},{"SUB", 200}, {"BRA",600}, {"BRZ", 700}, {"BRP",800}, {"LDA", 700}, {"STA", 300}, {"HLT", 0}, {"OUT", 902}};
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
    vector<string> memory = {"000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "009", "000", "000", "000", "000"};
 /*
    const int d = lines.size();
    int e;
    for(int i=0; i<d;i++){
        e = lines[i].size();
        for (int j=0; j<e;j++){
            cout << i << " " << j << " "<< lines[i][j] << endl;
        } 
    }*/
    vector<string> c;
    int k;
    const int lineLength = lines.size();
    int val;
    for(int i=0; i<lineLength;i++){
        c = lines[i];
        if (mainfunctions.count(c[0])){
            if (linearSearch(dontrequireinput, c[0])){
                if(c[0] == "HLT"){
                    memory[i] = "000";
                }else{
                    memory[i] = to_string(mainfunctions[c[0]]);
                }
            }else{
                val = stoi(getValue(c[c.size()-1]));
                memory[i] = to_string(mainfunctions[c[0]]+val);
            }
        } 
        
    }
    const int sizeOfMemory = memory.size();
    for(int l=0; l<sizeOfMemory; l++){
        cout << memory[l] << endl;
    }
}


