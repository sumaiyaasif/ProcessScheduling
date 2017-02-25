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
    int processCompletionTime;
    int eventCompletionTime;
    statusType statusType;
};

class Disk {
public:
    bool empty;
    int nextFreeTime;
};

class Core{
public:
    bool occupied = false;
    int coreCompletionTime;
    Process pid;
};

queue<Process> readyQueue;
queue<Process> diskQueue;
vector<Process> processVector;
vector<pair<string, int> > dataInput;


int slice;
int numOfProcesses = 0;
int simClock = 0;
int requestedTime = 0;
int availableCores;
vector<Core> coreVector;
int lastEventEndTime;

/* This splits the data read in into multiple Processes separated by the word "NEW". Does not take any arguments. Does not return anything. */
void splitDataInputIntoIndividualProcesses(){
    processVector.resize(numOfProcesses);
    int j = 0;
    int i = 0;
    while (i < dataInput.size()) {
        if(dataInput[i].first == "NEW"){
            processVector[j].statusType = READY;
            processVector[j].pid = j;
            if(i == 2){
                processVector[j].firstLine = i;
                processVector[j].currentLine = i;
            }
            else{
                processVector[j].firstLine = i;
                processVector[j].currentLine = i;
            }
            processVector[j].startTime = dataInput[i].second;
            i++;
            while (dataInput[i].first != "NEW" && i < dataInput.size()){
                processVector[j].lastLine = i;
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
            coreVector.resize(durationInt);
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
//void printIndividualProcesses() {
//    for (int i = 0; i < processVector.size(); i++) {
//        cout << "Start Time for process " << i << ": " << processVector[i].startTime << endl;
//        cout << "number of commands in process " << i << ":" << processVector[i].commands.size() << endl;
//        int processVectorCommandsSize = processVector[i].commands.size(); //setting size now because when we pop, the size changes which lead to not each one getting printed
//        for (int j = 0; j < processVectorCommandsSize; j++) {
//            cout << processVector[i].commands.front().first << ", " << processVector[i].commands.front().second << endl;
//            processVector[i].commands.pop();
//        }
//    }
//}

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

int numOfBusyCores(){
    int numOfBusyCores = 0;
    for(vector<Core>::iterator j = coreVector.begin(); j != coreVector.end(); j++){
        if(j->occupied){
            numOfBusyCores++;
        }
    }
    return numOfBusyCores;
}

void printProcessStatus(statusType status){
    if(status == READY)
        cout << "READY";
    if(status == RUNNING)
        cout << "RUNNING";
    if(status == BLOCKED)
        cout << "BLOCKED";
    if(status == TERMINATED)
        cout << "TERMINATED";
}
void printProcessTable(){
    cout << "PROCESS TABLE: " << endl;
    cout << "Process:   startTime   startLine   endLine    currentLine    status" << endl;
    for(vector<Process>::iterator j = processVector.begin(); j != processVector.end(); j++){
        cout << j->pid <<  "             " << j->startTime << "          " << j->firstLine << "           " << j->lastLine << "             " << j->currentLine << "          ";
        printProcessStatus(j->statusType);
        cout << endl;
    }
}
void printReadyQueue(){
    if(readyQueue.empty()){
        cout << "EMPTY";
    }
    else{
        for (int i = 0; i < readyQueue.size(); i++){
            cout << "Process: " << readyQueue.front().pid << " ";
            readyQueue.push(readyQueue.front());
            readyQueue.pop();
        }
    }
}

void printDiskQueue(){
    if(diskQueue.empty()){
        cout << "EMPTY";
    }
    else{
        for (int i = 0; i < diskQueue.size(); i++){
            cout << "Process: " << diskQueue.front().pid << " ";
            diskQueue.push(diskQueue.front());
            diskQueue.pop();
        }
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
        cout << "Process: " << j->pid << " started at " << j->startTime << " ms and is ";
        printProcessStatus(j->statusType);
        cout << endl;
        
    }
    
}
void coreRequest(Process &process){
    int eventStartTime = simClock;
    if(dataInput[process.currentLine].first == "NEW"){
        process.currentLine++; //go to Core command if its a new process otherwise stay on line
    }
    if(numOfBusyCores() < coreVector.size()){
        cout << "THERE IS A FREE CORE. POP PROCESS OUT OF READY QUEUE" << endl;
        readyQueue.pop();
        for(vector<Core>::iterator x = coreVector.begin(); x != coreVector.end(); x++){
            if(x->occupied == false){
                cout << "TAKE A CORE " << endl;
                x->occupied = true;
                x->pid = process;
                x->coreCompletionTime = eventStartTime + dataInput[process.currentLine].second;
                cout << "EVENT WILL GO FROM : " << eventStartTime << " TILL " << x->coreCompletionTime << endl;
                process.eventCompletionTime = x->coreCompletionTime;
                lastEventEndTime = x->coreCompletionTime;
                if(x->coreCompletionTime > simClock){
                    x->occupied = true;
                    process.statusType = RUNNING;
                }
                break;
            }
        }
   
    }
    else{
        cout << "THERE ARE NO FREE CORES. STAY IN READY QUEUE." << endl;
    }

}
void toReadyQueue(Process &process){
    readyQueue.push(process);
    coreRequest(process);
    
}

void processHandler(Process &process){
    if(dataInput[process.currentLine].first == "CORE"){
        cout << "Recieved a new CORE request" << endl;
        toReadyQueue(process);
        
    }
    else if(process.statusType == RUNNING){
        //
    }
    
}

bool checkIfProcessesRunning(){
    for(vector<Process>::iterator j = processVector.begin(); j != processVector.end(); j++){
        if(!(j->statusType == TERMINATED)){
            return true;
        }
    }
    return false;
}
// ones a command completes = currentLine++;
int main() {
    readFile();
    
    // START processes
    simClock = 0;
    for(vector<Process>::iterator j = processVector.begin(); j != processVector.end(); j++){
        cout << "FIRST EVENT PROCESS " << j->pid << endl;
        simClock = j->startTime; // set clock to the process startTime
        cout << "simClock " << simClock << endl;
        toReadyQueue(*j);   // send process to readyQueue
    }
    while (checkIfProcessesRunning()){ // While we are not at the end of our dataTable
        for(vector<Process>::iterator j = processVector.begin(); j != processVector.end(); j++){ // Go through vectors 0 and 1 again and again
            if(processVector.size() > 0){
                if(j->currentLine < j-> lastLine){ // if currentLine is not the last line for that process
                    if(j-> currentLine-1 != j-> firstLine && (lastEventEndTime == simClock)){ // if currentLine is not the first CORE request
                        processHandler(*j); // do some scheduling
                        cout << "simClock " << simClock << endl;
                    }
                    
                }
                else if(j->currentLine == j->lastLine){
                    processHandler(*j);
                    if(j->processCompletionTime == simClock){
                        j->statusType = TERMINATED;
                        printSummary();
                    }
                    
                }
                // check if any of the cores have freed up and moves whatever is in the queue into them
                for(vector<Core>::iterator x = coreVector.begin(); x != coreVector.end(); x++){
                    if(x->coreCompletionTime == simClock){
                        x-> occupied = false;   // change the core status to free
                        j->currentLine += 1;
                        cout << "CORE just freed up" << endl;
                        if(!readyQueue.empty()){    // move whatever is in the readyQueue to a core
                            
                            coreRequest(readyQueue.front());
                            
                        }
                    }
                }
            }
            else{
                exit(0);
            }
            
        }
//        if(j->processCompletionTime == simClock){
//            j->currentLine++;
//        }
        simClock++;
        if(simClock == 154){
            cout << "hele";
            if(simClock == 20){
                cout << "LOL";
            }
        }
        
    }
    
    return 0;
}

