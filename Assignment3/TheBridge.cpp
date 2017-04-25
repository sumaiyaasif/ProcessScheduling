#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define NUM_THREADS	1

int static maxBridgeLoad = 10;
int static currectBridgeLoad = 0;

static pthread_mutex_t mylock;
pthread_cond_t ok = PTHREAD_COND_INITIALIZER;
//unsigned int sleep(unsigned int seconds);

string licensePlate;
int arrivalTimeInt;
int vehicleWeightInt;
int timeToCrossInt;

struct thread_data *my_data;

struct thread_data{
   string  thread_id;
   int arrivalTimeInt;
   int vehicleWeightInt;
   int timeToCrossInt;
};

void enterBridge(int vehicleWeightInt){
	currectBridgeLoad = currectBridgeLoad + vehicleWeightInt;
	cout << "Vehicle: " << my_data->thread_id << " is CROSSING the bridge. Current bridge load is: " << currectBridgeLoad << endl;
}

void leaveBridge(int vehicleWeightInt){
	currectBridgeLoad = currectBridgeLoad - vehicleWeightInt;
	cout << "Vehicle: " << my_data->thread_id << " is LEAVING the bridge. Current bridge load is: " << currectBridgeLoad << endl;
}

void *PrintHello(void *threadarg) {
   

   my_data = (struct thread_data *) threadarg;

   cout << "Vehicle: " << my_data->thread_id << " has ARRIVED at bridge. Current bridge load is: " << currectBridgeLoad << endl;
   // If bridge load + vehichle weight <= maxBridgeLoad
   		// enterBridge(weight);
   		// sleep(timeToCrossInt);
   		// leaveBridge(weight);
   // If vehicle weight > maxBridgeLoad
   		// Vehicle will not cross and thread will exit
   // Else
   		// Vehicle will wait before crossing
   		// pthread_mutex_lock(&access);
   		//	while(vehicle weight > bridge load + vehicle weight)
   		//		pthread_cond_wait(&ok, &access);
   		// pthread_mutex_unlock(&access);
   if(currectBridgeLoad + vehicleWeightInt <= maxBridgeLoad){
   		enterBridge(vehicleWeightInt);
   		sleep(timeToCrossInt);
   		leaveBridge(vehicleWeightInt);
   }
   else if(vehicleWeightInt > maxBridgeLoad){
   		//
   }
   else{
   		pthread_mutex_lock(&mylock);
   		while(vehicleWeightInt > currectBridgeLoad + vehicleWeightInt){
   			pthread_cond_wait(&ok, &mylock);
   		}
   		pthread_mutex_unlock(&mylock);
   }
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
	
	sleep(arrivalTimeInt);
	 
	cout << "License Plate: " << licensePlate << " Arrival Time: " << arrivalTimeInt << " Weight: " << vehicleWeightInt << " Time To Cross: " << timeToCrossInt << endl;

	int rc;

       td[i].thread_id = licensePlate;
      rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
      pthread_join(threads[i], NULL);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
	}
	// pthread_create(%licensePlate, NULL, vehicle, (void *)&td);
}

int main(int argc, char *argv[])
{
	
	pthread_mutex_init(&mylock, NULL);

	readFile();
    pthread_exit(NULL);
}