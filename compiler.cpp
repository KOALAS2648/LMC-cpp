#include <iostream>
#include <fstream>
#include<vector>
#include<sstream>
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
 /*
    const int d = lines.size();
    int e;
    for(int i=0; i<d;i++){
        e = lines[i].size();
        for (int j=0; j<e;j++){
            cout << i << " " << j << " "<< lines[i][j] << endl;
        }
    
        
    }*/

    

}


