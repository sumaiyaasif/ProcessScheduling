#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>


using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017


vector<pair<string, int> > processes;
int slice;
bool readyQueueBusy = false;
bool coreBusy = false;

/* Reads file and stores it into a vector of pairs. Does not take any arguments. Does not output or return anything. */
void readFile() {
	string data;
	string duration;
	int durationInt;
	//make sure last line in file is not empty
	while (!cin.eof()) {
		getline(cin, data, ' ');
		getline(cin, duration);
		durationInt = atoi(duration.c_str());
		processes.push_back(make_pair(data, durationInt));
	}
}

/* Prints processes with their durations. Does not take any arguments. Does not return anything. */
void printProcesses() {
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].first << ", " << processes[i].second << endl;
	}
}

/* Get slice amount */
int getSlice() {
	for (int i = 0; i < processes.size(); i++) {
		if (processes[i].first == "SLICE") {
			slice = processes[i].second;
			break;
		}

	}
	return slice;
}

int main() {
	readFile();
	printProcesses();
	
	return 0;
}




