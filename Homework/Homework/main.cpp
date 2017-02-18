#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>

using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017
class Process {
public:
    int startTime;
    vector<pair<string, int> > commands;
};

vector<pair<string, int> > dataInput;
vector<Process> processVector;
int totalCores;
int slice;
int numOfProcesses = 0;

/* Reads file and stores it into a vector of pairs. Breaks Core requests larger than slice allowance into multiple core requests. Does not take any arguments. Does not output or return anything. */
void readFile() {
    string data;
    string duration;
    int durationInt;
    
    //make sure last line in file is not empty
    while (!cin.eof()) {
        getline(cin, data, ' ');
        getline(cin, duration);
        durationInt = atoi(duration.c_str());
        if(data == "NCORE"){
            totalCores = durationInt;
        }
        else if(data == "SLICE"){
            slice = durationInt;
        }
        else if(data == "NEW"){
            numOfProcesses++;
        }
        while(data == "CORE" && durationInt > slice){
            dataInput.push_back(make_pair(data, slice));
            durationInt = durationInt - slice;
        }
        dataInput.push_back(make_pair(data, durationInt));
    }
    
    processVector.resize(numOfProcesses);
    int j = 0;
    for (int i = 0; i < dataInput.size(); i++) {
        if(dataInput[i].first == "NEW"){
            processVector[j].startTime = dataInput[i].second;
            i++;
            while (dataInput[i].first != "NEW"){
                processVector[j].commands.push_back(make_pair(dataInput[i].first, dataInput[i].second));
                i++;
            }
            j++;
        }
    }
}

/* Prints dataInput with their durations. Does not take any arguments. Does not return anything. */
void printdataInput() {
    // for (int i = 0; i < dataInput.size(); i++) {
    // 	cout << dataInput[i].first << ", " << dataInput[i].second << endl;
    // }
    
    cout << processVector.size() << endl;
    
    for (int i = 0; i < processVector.size(); i++) {
        cout << "Start Time for process " << i << ": " << processVector[i].startTime << endl;
        for (int j = 0; j < processVector[i].commands.size(); j++) {
            cout << processVector[i].commands[j].first << ", " << processVector[i].commands[j].second << endl;
        }
    }
}

int main() {
    readFile();
    printdataInput();
    return 0;
}
