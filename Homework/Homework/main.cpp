#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017
enum statusType{RUNNING, TERMINATED};
enum processStage{readyQue, core, diskQue, disk, display, notStarted, terminated};

class Process {
public:
    int startTime;
    vector<pair<string, int> > commands;
    statusType processStatus;
    processStage processStage;
};

class Core {
public:
    bool empty;
    int nextFreeTime;
};

class Disk {
public:
    bool empty;
    int nextFreeTime;
};

queue<Process> readyQueue;
queue<Process> diskQueue;

vector<pair<string, int> > dataInput;
vector<Process> processVector;
vector<Core> coreVector;
int totalCores;
int slice;

int numOfProcesses = 0;
/* Reads file and stores it into a vector of pairs. Breaks Core requests larger than slice allowance into multiple core requests. Does not take any arguments. Does not output or return anything. */
void readFile() {
    string data;
    string duration;
    int durationInt;
    
    //make sure last line in file is not empty
    ifstream infile("sample.txt");
    while (!infile.eof()) {
        getline(infile, data, ' ');
        getline(infile, duration);
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
}

/*This splits the data read in into multiple Processes separated by the word "NEW". Does not take any arguments. Does not return anything. */
void splitDataInputIntoIndividualProcesses(){
    processVector.resize(numOfProcesses);
    int j = 0;
    int i = 0;
    while (i < dataInput.size()) {
        if(dataInput[i].first == "NEW"){
            processVector[j].startTime = dataInput[i].second;
            i++;
            while (dataInput[i].first != "NEW" && i < dataInput.size()){
                processVector[j].commands.push_back(make_pair(dataInput[i].first, dataInput[i].second));
                i++;
            }
            j++;
        } else {
            i++;
        }
    }
}

/* Prints dataInput with their durations. Does not take any arguments. Does not return anything. */
void printdataInput() {
    for (int i = 0; i < dataInput.size(); i++) {
        cout << dataInput[i].first << ", " << dataInput[i].second << endl;
    }
}

/*Prints each process along with its list of events and its start times. Does not take any arguments. Does not return anything.*/
void printIndividualProcesses() {
    for (int i = 0; i < processVector.size(); i++) {
        cout << "Start Time for process " << i << ": " << processVector[i].startTime << endl;
        for (int j = 0; j < processVector[i].commands.size(); j++) {
            cout << processVector[i].commands[j].first << ", " << processVector[i].commands[j].second << endl;
        }
    }
}

int countTerminatedProcesses(){
    int terminatedProcesses = 0;
    for(int i = 0; i < processVector.size(); i++){
        if(processVector[i].processStatus == TERMINATED ){
            terminatedProcesses++;
        }
    }
    return terminatedProcesses;
}

void createCoreObjects(){
    int coresCreated = 0;
    int i = 0;
    while (coresCreated < totalCores){
        coreVector[i].empty = true;
        i++;
    }
}
void processHandler(){
    int i = 0;
    int j = 0;
    if(processVector[i].startTime == 0){
        //put process into core for requested time
        //mark core busy until requested time
        if(processVector[i++].startTime < coreVector[j].nextFreeTime){
            processVector[i++].processStage = readyQue;
            readyQueue.push(processVector[i++]);
        }
    }
    
}

int main() {
    readFile();
    splitDataInputIntoIndividualProcesses();
    printIndividualProcesses();
    while (countTerminatedProcesses() < processVector.size()){
        processHandler();
    }
    return 0;
}
