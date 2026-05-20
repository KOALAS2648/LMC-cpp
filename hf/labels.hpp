#include<vector>
#include <string>
#include<map>
using namespace std;
namespace GetLabel
{
    map<string, int> getLabels(vector<vector<string>>* code, map<string, int> mainFunctions)
    {
    map<string, int> labels = {};
    vector<vector<string>> &sourcecode = *code;
    const int numberoflines = sourcecode.size();

    vector<string> line;
    for(int j=0; j<numberoflines;){
        line=sourcecode[j];
        if ((mainFunctions.find(line[0])==mainFunctions.end()) && (line[1] != "DAT")){
            labels[line[0]] = j;
            sourcecode[j].erase(sourcecode[j].begin());

        }else{
            j++;
        }
    }
    return labels;
}
} 