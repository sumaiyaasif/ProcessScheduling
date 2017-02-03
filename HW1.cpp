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
   vector<pair<string, int> > processes;
   while(!cin.eof()){
   	getline(cin, data, ' ');
   	getline(cin, duration);
   	cout << data << endl;
   	cout << duration << endl;
   	
   }
   

   return 0;
}