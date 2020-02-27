#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

void initVar(string[][10]);
void initConc(string[][10]);
void initClause(int clause[], string conc[][10]);
bool checkConclusion(stack<int> concStack, int clause[], string var[][10], string conc[][10]);
bool checkVariable(int num, string var[][10]);


int main(){

    string var[3][10];
    initVar(var);

    string conc[2][10];
    initConc(conc);

    int clause[100] = {0};
    initClause(clause, conc);

    // create conclusion stack
    stack <int> concStack;
    for (int i = 10; i > 0; i--){
        concStack.push(i);
    }

    bool success = checkConclusion(concStack, clause, var, conc);

    return 0;
}

void initVar(string var[][10]){

    string varName;
    string node;
    ifstream file ("variables.txt");

    for (int i = 0; i < 10; i++){

        getline(file, varName);
        var[0][i] = varName;

        getline(file, node);
        var[1][i] = node;

        var[2][i] = "NI";
    }
    file.close();
}

void initConc(string conc[][10]){

    string concName;
    string path;
    ifstream file ("conclusions.txt");

    for (int i = 0; i < 10; i++){

        getline(file, concName);
        conc[0][i] = concName;

        getline(file, path);
        conc[1][i] = path;
    }
    file.close();
}

void initClause(int clause[], string conc[][10]){

    for (int i = 0; i < 10; i++){

        // Get location of each rule in clause list
        int location = (i * 10) + 1;


        // Convert path string from conclusion list to array of ints
        string pathString = conc[1][i];
        int length = pathString.length();
        int path[length] = { 0 };

        int x = 0;

        for (int y = 0; pathString[y] != '\0'; y++) {

            if (pathString[y] == ',') {
                x++;
            }
            else {
                path[x] = path[x] * 10 + (pathString[y] - 48);
                //cout << path[x];
            }
        }
        // Assign rules to clause list
        for (int j = 0; j <= length; j++){

            int ruleNum = path[j];
            clause[(j + location)] = ruleNum;
        }
    }
}

bool checkConclusion(stack<int> concStack, int clause[], string var[][10], string conc[][10]){

    int ruleNum = concStack.top();
    int varNum;
    bool success = false;

    // Get the location in clause list for the rule
    ruleNum = ((ruleNum - 1) * 10) + 1;
    int ruleLen = 0;

    // Go to end of rule to work backwards
    while (clause[ruleNum] != 0){
        ruleLen++;
        ruleNum++;
    }

    // Check each variable of rule
    for (int i = (ruleLen - 1); i > 0; i--){

        varNum = clause[i];

        // Find associated variable
        for (int i = 0; i < 10; i++){

            string node = var[1][i];
            int nodeNum = stoi(node);
            if (varNum == nodeNum){
                // Check if node is initialized and value
                success = checkVariable(i, var);
                break;
            }
        }
    }

    return true;
}

bool checkVariable(int num, string var[][10]){

    if (var[2][num] == "NI"){
        // Initialize Variable
    }
    // If variable has already been initialized
    else if(var[2][num] == "YES"){
        return true
    }
    else if(var[2][num] == "NO"){
        return false;
    }
    return true;
}



