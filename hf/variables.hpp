#include <vector>
#include < map>
#include <string>
using namespace std;
namespace GetVariables
{
    map<string,  int> getVariables(vector<vector<string>>* code, map<string, int> mainFunctions){
    map<string,  int> variables = {};
    vector<vector<string>> &sourcecode = *code;
    const int numberoflines = sourcecode.size();
    string varname;
    vector<string> line;
    for(int j=0; j<numberoflines; j++){
        line=sourcecode[j];
        
        if (mainFunctions.find(line[0])==mainFunctions.end()){
            if ((line[1] == "DAT")){
                varname = line[0];
                variables[varname] = j;
                sourcecode[j].erase(sourcecode[j].begin());

            }
        }
        
    }
    return variables;
}
}