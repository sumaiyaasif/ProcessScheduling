#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>

using namespace std;

#define NUM_THREADS	7

int static maxBridgeLoad;
int static currectBridgeLoad = 0;

static pthread_mutex_t mylock;
pthread_cond_t ok = PTHREAD_COND_INITIALIZER;

struct thread_data{
   string  thread_id;
   int arrivalTimeInt;
   int vehicleWeightInt;
   int timeToCrossInt;
};

void enterBridge(struct thread_data *my_data){
	pthread_mutex_lock(&mylock);
	currectBridgeLoad = currectBridgeLoad + my_data->vehicleWeightInt;
	cout << "Vehicle: " << my_data->thread_id << " is CROSSING the bridge. Current bridge load is: " << currectBridgeLoad << endl;
	pthread_mutex_unlock(&mylock);
}

void leaveBridge(struct thread_data *my_data){
	pthread_mutex_lock(&mylock);
	currectBridgeLoad = currectBridgeLoad - my_data->vehicleWeightInt;
	cout << "Vehicle: " << my_data->thread_id << " is LEAVING the bridge. Current bridge load is: " << currectBridgeLoad << endl;
	pthread_cond_signal(&ok);
	pthread_mutex_unlock(&mylock);
}

void *PrintHello(void *threadarg) {
   
   struct thread_data *my_data = (struct thread_data *) threadarg;

   cout << "Vehicle: " << my_data->thread_id << " has ARRIVED at bridge. Current bridge load is: " << currectBridgeLoad << endl;
   
   // Vehicle will NOT be allowed on the bridge ever
   if(my_data->vehicleWeightInt > maxBridgeLoad){
   		cout << "Vehicle: " << my_data->thread_id << " exceeds the max bridge hold. It will not be allowed to cross." << endl;
   		pthread_exit(NULL);
   }
   // Vehicle will be allowed onto the bridge after some wait time
   pthread_mutex_lock(&mylock);
   while(my_data->vehicleWeightInt + currectBridgeLoad > maxBridgeLoad){
   		pthread_cond_wait(&ok, &mylock);
   }
   pthread_mutex_unlock(&mylock);
   pthread_cond_signal(&ok);
   // Vehicle will be allowed onto the bridge immediately
   enterBridge(my_data);
   sleep(my_data->timeToCrossInt);
   leaveBridge(my_data);

   pthread_exit(NULL);
}

void readFile(){

}

int main(int argc, char *argv[])
{
	// ifstream inputFile(argv[1]);
	// if(!inputFile.is_open()){
	// 	cout << "Could not open file.\n";
	// 	exit(0);
	// }
	string x;
	string licensePlate;
	int arrivalTimeInt;
	int vehicleWeightInt;
	int timeToCrossInt;
	string arrivalTime;
	string vehicleWeight;
	string timeToCross;	
	maxBridgeLoad = atoi(argv[1]);
	cout << "Maximum bridge load is " << maxBridgeLoad << endl;
	pthread_t threads[NUM_THREADS];
	struct thread_data td[NUM_THREADS];
	pthread_mutex_init(&mylock, NULL);
	int i = 0;
	while(cin >> licensePlate) {
		//cin >> licensePlate;
		cin >> arrivalTime;
		cin >> vehicleWeight;
		cin >> timeToCross;

		td[i].arrivalTimeInt = atoi(arrivalTime.c_str());
	 	td[i].vehicleWeightInt = atoi(vehicleWeight.c_str());
	 	td[i].timeToCrossInt = atoi(timeToCross.c_str());
	 	td[i].thread_id = licensePlate;

	 sleep(td[i].arrivalTimeInt);
	 
	 cout << "License Plate: " << td[i].thread_id << " Arrival Time: " << td[i].arrivalTimeInt << " Weight: " << td[i].vehicleWeightInt << " Time To Cross: " << td[i].timeToCrossInt << endl;

	 int rc;

     rc = pthread_create(&threads[i], NULL, PrintHello, (void *)&td[i]);
     if (rc){
     	cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
       }
       i++;
	}

	 for (int i = 0; i < NUM_THREADS; i++){
	 	pthread_join(threads[i], NULL);
	 }
	  	
	 
	 readFile();
     pthread_exit(NULL);
}