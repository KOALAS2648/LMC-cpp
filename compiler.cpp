#include <iostream>
#include <fstream>
#include<vector>
#include<sstream>
#include <string>
#include<map>
using namespace std;

map<string, int> getLabels(vector<vector<string>>* code, map<string, int> mainFunctions){
    map<string, int> labels = {};
    vector<vector<string>> sourcecode = *code;
    const int numberoflines = sourcecode.size();

    vector<string> line;
    for(int j=0; j<numberoflines; j++){
        line=sourcecode[j];
        if (!(mainFunctions.count(line[0])==1) && (line[1] != "DAT")){
            labels[line[0]] = j;
            cout << j << endl;
            sourcecode[j].erase(sourcecode[j].begin());

        }
    }
    return labels;
}

map<string, int> getVariables(vector<vector<string>>* code, map<string, int> mainFunctions){
    map<string, int> variables = {};
    vector<vector<string>> sourcecode = *code;
    const int numberoflines = sourcecode.size();

    vector<string> line;
    for(int j=0; j<numberoflines; j++){
        line=sourcecode[j];
        if (!(mainFunctions.count(line[0])==1) && (line[1] == "DAT")){
            variables[line[0]] = j;
            cout << j << endl;
            sourcecode[j].erase(sourcecode[j].begin());

        }
    }
    return variables;
}
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
    vector<vector<string>>* ptr = &lines;
    map<string, int> labels = getLabels(ptr, mainfunctions);
    map<string, int> variables = getVariables(ptr, mainfunctions);
    cout << "hello world" << endl;
    vector<string> memory = {"000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "000", "000", "000", "000", "000","000", "000", "000", "000", "000", "009", "000", "000", "000", "000"};
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
    for (const auto& [key, value] : labels) {
        cout << key << " : " << value << endl;
    }
    for (const auto& [key, value] : variables) {
        cout << key << " : " << value << endl;
    }

    
    return 0;
}


