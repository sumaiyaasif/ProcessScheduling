#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define NUM_THREADS	5

int static maxBridgeLoad = 10;
int static currectBridgeLoad;

struct thread_data{
   int  thread_id;
   char *message;
};

void *PrintHello(void *threadarg) {
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Thread ID : " << my_data->thread_id ;
   cout << " Message : " << my_data->message << endl;

   pthread_exit(NULL);
}

// void readFile(){

// 	string licensePlate;
// 	string arrivalTime;
// 	string vehicleWeight;
// 	string timeToCross;
// 	int arrivalTimeInt;
// 	int vehicleWeightInt;
// 	int timeToCrossInt;
// 	ifstream infile("sample.txt");
// 	infile >> ws;
// 	getline(infile, licensePlate, ' ');
// 	infile >> ws;
// 	getline(infile, arrivalTime, ' ');
// 	infile >> ws;
// 	getline(infile, vehicleWeight, ' ');
// 	infile >> ws;
// 	getline(infile, timeToCross);

// 	arrivalTimeInt = atoi(arrivalTime.c_str());
// 	vehicleWeightInt = atoi(vehicleWeight.c_str());
// 	timeToCrossInt = atoi(timeToCross.c_str());

// 	cout << "License Plate: " << licensePlate << " Arrival Time: " << arrivalTimeInt << " Weight: " << vehicleWeightInt << " Time To Cross: " << timeToCrossInt << endl;

// 	sleep(arrivalTime);
// 	for (int i = 0; i < NUM_THREADS; i++){
		
// 	}
// 	pthread_create(%licensePlate, NULL, vehicle, (void *)&td);
// }

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	//readFile();
	int rc;
   int i;
	   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].thread_id = i;
      td[i].message = (char *)"This is message";
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
		
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
	
   pthread_exit(NULL);
}