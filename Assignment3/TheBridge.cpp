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

string licensePlate;
int arrivalTimeInt;
int vehicleWeightInt;
int timeToCrossInt;

struct thread_data{
   string  thread_id;
   char *message;
};

void *PrintHello(void *threadarg) {
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;

   cout << "Vehicle: " << my_data->thread_id << " has ARRIVED at bridge." <<endl;

   pthread_exit(NULL);
}

void readFile(){
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];

	string arrivalTime;
	string vehicleWeight;
	string timeToCross;	
	ifstream infile("sample.txt");
	for (int i = 0; i < NUM_THREADS; i++){
	infile >> ws;
	getline(infile, licensePlate, ' ');
	infile >> ws;
	getline(infile, arrivalTime, ' ');
	infile >> ws;
	getline(infile, vehicleWeight, ' ');
	infile >> ws;
	getline(infile, timeToCross);

	arrivalTimeInt = atoi(arrivalTime.c_str());
	vehicleWeightInt = atoi(vehicleWeight.c_str());
	timeToCrossInt = atoi(timeToCross.c_str());
	
	// sleep(arrivalTime);
	 
	cout << "License Plate: " << licensePlate << " Arrival Time: " << arrivalTimeInt << " Weight: " << vehicleWeightInt << " Time To Cross: " << timeToCrossInt << endl;

	int rc;

       td[i].thread_id = licensePlate;
      td[i].message = (char *)"This is message";
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
		
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
	}
	// pthread_create(%licensePlate, NULL, vehicle, (void *)&td);
}

int main(int argc, char *argv[])
{
	
	
	//readFile();
	
	//for( i=0; i < NUM_THREADS; i++ ){
		readFile();
   //    cout <<"main() : creating thread, " << i << endl;
   //    cout << "License Plate: " << licensePlate << " Arrival Time: " << arrivalTimeInt << " Weight: " << vehicleWeightInt << " Time To Cross: " << timeToCrossInt << endl;

   
   // //}
	
   pthread_exit(NULL);
}