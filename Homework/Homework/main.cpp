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
enum statusType{READY, RUNNING, BLOCKED, TERMINATED};
class Process {
public:
    int pid;
    int startTime;
    int firstLine;
    int lastLine;
    int currentLine;
    queue<pair<string, int> > commands;
    statusType statusType;
};

class Disk {
public:
    bool empty;
    int nextFreeTime;
};


queue<Process> readyQueue;
queue<Process> diskQueue;
vector<Process> processVector;
vector<pair<string, int> > dataInput;


int slice;
int numOfProcesses = 0;
int simClock = 0;
int requestedTime = 0;
int pa = 0;
int availableCores;
list<int> totalCores;


/* This splits the data read in into multiple Processes separated by the word "NEW". Does not take any arguments. Does not return anything. */
void splitDataInputIntoIndividualProcesses(){
    processVector.resize(numOfProcesses);
    int j = 0;
    int i = 0;
    while (i < dataInput.size()) {
        if(dataInput[i].first == "NEW"){
            processVector[j].pid = j;
            if(i == 2){
                processVector[j].firstLine = i + 1;
            }
            else{
                processVector[j].firstLine = i;
            }
            processVector[j].startTime = dataInput[i].second;
            i++;
            while (dataInput[i].first != "NEW" && i < dataInput.size()){
                processVector[j].lastLine = i -1;
                i++;
            }
            j++;
        } else {
            i++;
        }
    }
}

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
        if(data == "NCORES"){
            totalCores.assign (durationInt, 0);
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
    splitDataInputIntoIndividualProcesses();
}

/* Prints dataInput with their durations. Does not take any arguments. Does not return anything. */
void printdataInput() {
    for (int i = 0; i < dataInput.size(); i++) {
        cout << dataInput[i].first << ", " << dataInput[i].second << endl;
    }
}

/* Prints each process along with its list of events and its start times. Should not use this for the program as it pops off the commands from each process but only using to help build program. Does not take any arguments. Does not return anything.*/
void printIndividualProcesses() {
    for (int i = 0; i < processVector.size(); i++) {
        cout << "Start Time for process " << i << ": " << processVector[i].startTime << endl;
        cout << "number of commands in process " << i << ":" << processVector[i].commands.size() << endl;
        int processVectorCommandsSize = processVector[i].commands.size(); //setting size now because when we pop, the size changes which lead to not each one getting printed
        for (int j = 0; j < processVectorCommandsSize; j++) {
            cout << processVector[i].commands.front().first << ", " << processVector[i].commands.front().second << endl;
            processVector[i].commands.pop();
        }
    }
}

/* Counts number of processes that have gone through the scheduler and have completed all their commands. Returns the number of those completed processes. Takes no arguments.*/
int countTerminatedProcesses(){
    int terminatedProcesses = 0;
    for(int i = 0; i < processVector.size(); i++){
        if(processVector[i].statusType == TERMINATED ){
            terminatedProcesses++;
        }
    }
    return terminatedProcesses;
}

void processHandler(){
    if (processVector[pa].startTime == simClock ){
        
    }
}

int numOfBusyCores(){
    int numOfBusyCores = 0;
    for(list<int>::iterator j = totalCores.begin(); j != totalCores.end(); j++){
        if(*j == 1){
            numOfBusyCores++;
        }
    }
    return numOfBusyCores;
}

void printReadyQueue(){
    if(readyQueue.empty()){
        cout << "EMPTY";
    }

}

void printDiskQueue(){
    if(diskQueue.empty()){
        cout << "EMPTY";
    }
    
}

void printSummary(){
    cout << "CURRENT STATE OF THE SYSTEM AT t = " << simClock <<  endl;
    cout << "Current number of busy cores: " << numOfBusyCores() << endl;
    cout << "READY QUEUE: " << endl;
    printReadyQueue();
    cout << endl;
    cout << "DISK QUEUE: " << endl;
    printDiskQueue();
    cout << endl;
    cout << "PROCESS TABLE: " << endl;
    for(vector<Process>::iterator j = processVector.begin(); j != processVector.end(); j++){
        cout << "Process: " << j->pid << " started at " << j->startTime << " ms and is " << j->statusType << endl;
    }
    
}

int main() {
    readFile();
    printSummary();
//    printIndividualProcesses();
//    while (countTerminatedProcesses() < processVector.size()){
//        processHandler();
//        simClock++;
//    }
    return 0;
}

