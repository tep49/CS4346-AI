#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

void initVar(string[][10]);
void initConc(string[][10]);
void initClause(int clause[], string conc[][10]);
bool checkConclusion(stack<int> concStack, int clause[], string var[][10], string conc[][10]);
bool checkVariable(int num, string var[][10]);
bool initializeValue(int num);
void initVarFW(string[][5], string filename);
void initConcFW(string[][5], string filename);
void initClauseFW(int clause[], string conc[][5]);
bool checkVariableFW(int num, string var[][5]);

int main(){

    string var[3][10];
    initVar(var);

    string conc[3][10];
    initConc(conc);

    int clause[100] = {0};
    initClause(clause, conc);

    // Without this line, program will output a blank line instead of the word MEDICAL
    //      even though all other conclusion names output correctly.
    conc[0][0] = "MEDICAL";

    // create conclusion stack
    stack <int> concStack;
    for (int i = 9; i >= 0; i--){
        concStack.push(i);
    }

    bool success = 0;
    int conclusion;

    while (!success){
        conclusion = concStack.top();
        cout << "\nChecking conclusion " << conc[0][conclusion];
        success = checkConclusion(concStack, clause, var, conc);
        if (success){
            cout << "\nProfession: " << conc[0][conclusion];
        }
        else{
            concStack.pop();
        }
    }

    /************************************************************
                        Forward Chaining
    ************************************************************/

    string varFW[3][5];
    string concFW[2][5];
    int clauseFW[50] = {0};
    stack <int> concStackFW;
    string fileVar;
    string fileConc;
    int a = 0;
    switch(conclusion){
    case 0:
    fileVar = "med_vars.txt";
    fileConc = "med_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 1:
    fileVar = "sci_vars.txt";
    fileConc = "sci_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 2:
    fileVar = "eng_vars.txt";
    fileConc = "eng_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 3:
    fileVar = "ed_vars.txt";
    fileConc = "ed_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 4:
    fileVar = "fine_art_vars.txt";
    fileConc = "fine_art_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 5:
    fileVar = "pol_vars.txt";
    fileConc = "pol_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 6:
    fileVar = "law_vars.txt";
    fileConc = "law_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    };

    break;
    case 7:
    fileVar = "comm_vars.txt";
    fileConc = "comm_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 8:
    fileVar = "bus_vars.txt";
    fileConc = "bus_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    case 9:
    fileVar = "lib_art_vars.txt";
    fileConc = "lib_art_conc.txt";
    initVarFW(varFW, fileVar);
    initConcFW(concFW, fileConc);
    for (int i = 5; i > 0; i--){
    concStack.push(i);
    }

    break;
    }

/**output job to console **/

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
    string negPath;
    ifstream file ("conclusions.txt");

    for (int i = 0; i < 10; i++){

        getline(file, concName);
        conc[0][i] = concName;

        getline(file, path);
        conc[1][i] = path;

        getline(file, negPath);
        conc[2][i] = negPath;
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
    bool response;


    string pathString = conc[2][ruleNum];
    int length = pathString.length();
    int negPath[length] = { 0 };

    int x = 0;

    for (int y = 0; pathString[y] != '\0'; y++) {

        if (pathString[y] == ',') {
            x++;
        }
        else {
            negPath[x] = negPath[x] * 10 + (pathString[y] - 48);
        }
    }

    // Get the location in clause list for the rule
    ruleNum = ((ruleNum) * 10) + 1;
    int ruleLen = 0;

    // Go to end of rule to work backwards
    while (clause[ruleNum] != 0){
        ruleLen++;
        ruleNum++;
    }

    // Check each variable of rule
    for (int i = (ruleNum - 2); i > (ruleNum - (ruleLen + 1)); i--){

        varNum = clause[i];

        // Find associated variable
        for (int j = 0; j < 10; j++){

            string node = var[1][j];
            int nodeNum = stoi(node);
            if (varNum == nodeNum){
                // Check if node is initialized and value
                response = checkVariable(j, var);

                if ((response == true) && (varNum == nodeNum)){
                    success = true;
                    break;
                }
                else{
                    success = false;
                }
                for (int x = 0; x < length; x++){
                    if ((response == false) && (negPath[x] == varNum)){
                        success = true;
                        break;
                    }
                    else{
                        success = false;
                    }
                }
                if (success == false){
                    return false;
                }
                }
            }
        }

    return success;
}

bool checkVariable(int num, string var[][10]){

    bool val;
    if (var[2][num] == "NI"){
        val = initializeValue(num);
        if (val == true){
            var[2][num] = "YES";
        }
        else{
            var[2][num] = "NO";
        }
    }
    // If variable has already been initialized
    else if(var[2][num] == "YES"){
        val = true;
    }
    else if(var[2][num] == "NO"){
        val = false;
    }
    return val;
}

bool initializeValue(int num){

    ifstream file("questions.txt");
    string question;
    string questions[10];
    string response;
    bool input = 0;
    bool val;

    for (int i = 0; i < 10; i++){
        getline(file, question);
        questions[i] = question;
    }

    while (input == 0){
        cout << "\n" << questions[num];
        cin >> response;

        transform(response.begin(), response.end(), response.begin(), ::toupper);

        if (response.compare("YES") == 0){
            val = true;
            input = 1;
        }
        else if (response.compare("NO") == 0){
            val = false;
            input = 1;
        }
        else{
            cout << "\nIncorrect Input";
        }
    }

    return val;
}
/**************************************************
          Functions for forward chaining
**************************************************/

void initVarFW(string varFW[][5], string filename){

    string varName;
    string node;
    ifstream file (filename);

    for (int i = 0; i < 5; i++){

        getline(file, varName);
        varFW[0][i] = varName;

        getline(file, node);
        varFW[1][i] = node;

        varFW[2][i] = "NI";
    }
    file.close();
}

void initConcFW(string concFW[][5], string filename){

    string concName;
    string path;
    ifstream file (filename);

    for (int i = 0; i < 5; i++){

        getline(file, concName);
        concFW[0][i] = concName;

        getline(file, path);
        concFW[1][i] = path;
    }
    file.close();
}

void initClauseFW(int clauseFW[], string concFW[][5]){

    for (int i = 0; i < 5; i++){

        // Get location of each rule in clause list
        int location = (i * 10) + 1;


        // Convert path string from conclusion list to array of ints
        string pathString = concFW[1][i];
        int length = pathString.length();
        int path[length] = { 0 };

        int x = 0;

        for (int y = 0; pathString[y] != '\0'; y++) {

            if (pathString[y] == ',') {
                x++;
            }
            else {
                path[x] = path[x] * 10 + (pathString[y] - 48);/**change formula**/
                //cout << path[x];
            }
        }
        // Assign rules to clause list
        for (int j = 0; j <= length; j++){

            int ruleNum = path[j];
            clauseFW[(j + location)] = ruleNum;
        }
    }
}

