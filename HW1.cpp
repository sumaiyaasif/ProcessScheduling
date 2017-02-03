#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017

string data;
string duration;
vector<pair<string, string> > processes;
/* Reads file and stores it into a vector of pairs. Does not take any arguments. Does not output or return anything. */
void readFile() {
	//make sure last line in file is not empty
	while (!cin.eof()) {
		getline(cin, data, ' ');
		getline(cin, duration);
		processes.push_back(make_pair(data, duration));
	}
}
/* Prints processes with their durations. Does not take any arguments. Does not return anything. */
void printProcesses(){
	for (int i = 0; i < processes.size(); i++) {
		cout << processes[i].first << ", " << processes[i].second << endl;
	}
}
int main( ) {
	readFile();
	printProcesses();



	return 0;
}