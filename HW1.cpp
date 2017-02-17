#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <list>

using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017


vector<pair<string, int> > processes;
int cores;
int slice;
bool readyQueueBusy = false;
bool coreBusy = false;

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
			cores = durationInt;
		}
		else if(data == "SLICE"){
			slice = durationInt;
		}
		while(data == "CORE" && durationInt > slice){
			processes.push_back(make_pair(data, slice));
			durationInt = durationInt - slice;
		}
		processes.push_back(make_pair(data, durationInt));
	}
}

/* Prints processes with their durations. Does not take any arguments. Does not return anything. */
void printProcesses() {
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].first << ", " << processes[i].second << endl;
	}
}

void splitIndividualProcesses() {
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].first << ", " << processes[i].second << endl;
	}
}

int main() {
	readFile();
	
	return 0;
}




