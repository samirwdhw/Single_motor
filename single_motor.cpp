#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

#define F_MAX 1		//Maximum force acting on the motor
#define RATE_MAX 125	///Maximum rate in the process
#define THRESHOLD 0.2	//Time*rate <= THRESHOLD

float dist;		//For distance moved
float time1;		//For time
float p;	//Probability
float time_step = 1.0;	//Start with 1(convention)


float get_step(float rate){			//To calculate the appropriate time step

	//Enter code to calculate time_step

	while(time_step*rate > THRESHOLD){

		time_step /= 10;

	}

	cout<<time_step<<endl;
}



float rand1(){		//To generate values b/w 0,1

	float val = (float)rand()/(RAND_MAX);

	return val;
}
 

int main(){

	get_step(RATE_MAX);

	for(int force = 0; force< F_MAX; force++){

		dist = 0;
		
		for(int time1 = 0; ; time1 += time_step){

			float prob_check = rand1();

		}

	}


	return 0;
}