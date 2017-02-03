#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//Sumaiya Asif
//Operating Systems
//1 Feb 2017

int main( ) {

   int c;
   string data;
   string duration;
   vector<pair<string, string> > processes;
   //make sure last line in file is not empty
   while(!cin.eof()){
   	getline(cin, data, ' ');
   	getline(cin, duration);
   	processes.push_back(make_pair(data, duration));
   	
   }
   for(int i = 0; i < processes.size(); i++)
{
     cout << processes[i].first << ", " << processes[i].second << endl;
}

   

   return 0;
}