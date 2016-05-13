#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>

using namespace std;

#define F_MAX 5.0		//Maximum force acting on the motor
#define N_FORCE 100.0
#define FORCE_STEP F_MAX/N_FORCE	//Step size for force
#define RATE_MAX 125	///Maximum rate in the process
#define THRESHOLD 0.2	//Time*rate <= THRESHOLD
#define STEP_SIZE 8.0		//Size of one step by motor
#define N_RUNS 20000		//Number of runs for averaging
#define FILE_NAME_DIST "dist_avg.dat"	//To output distances
#define FILE_NAME_VELO "velo_avg.dat"	//To output velocity


float time1;		//For time
float p_step, p_detach;		//Probability
float time_step = 1.0;		//Start with 1(convention)

//For now(edit function to change these for other rates)

float rate_step;		//Rate of stepping at a particular force
float rate_detach;		//Rate of detaching at a particular force


float get_step(){			//To calculate the appropriate time step

	//Enter code to calculate time_step

	while(time_step * RATE_MAX > THRESHOLD){

		time_step /= 10;

	}
	//cout<<time_step<<endl;
}


void set_rate(float force){		//To set the probabilities for a particular Force

	float velo_temp = 1000 - 200*force;
	float dist_temp = 1000*exp(-1*force/3);

	rate_step = velo_temp/STEP_SIZE;
	rate_detach = velo_temp/dist_temp;

	p_step = time_step * rate_step;
	p_detach = time_step * rate_detach;
}


float rand1(){		//To generate values b/w 0,1

	float val = (float)rand()/(RAND_MAX);

	return val;
}
 

int main(){

	float dist_avg = 0;		//For average distance moved
	float velo_avg = 0;		//For average velocity
	float dist;		//For distance moved
	float time1;	//To increment time
	ofstream f1, f2; 	//To output data (velo, dist)

	f1.open(FILE_NAME_DIST);	//To output distance
	f2.open(FILE_NAME_VELO);	//To output velocity

	get_step();


	for(float force = 0; force <= F_MAX; force += FORCE_STEP){

		set_rate(force);

		for(int runs=  0; runs< N_RUNS; runs++){
			
			dist = 0;

			for(time1 = 0; ; time1 += time_step){

				float prob_check = rand1();

				if(prob_check < p_step){

					dist += STEP_SIZE;

				}

				else if(prob_check >= p_step && prob_check < p_step + p_detach){

					break;
				}

			}

			dist_avg += dist;

			if( dist != 0){
					
				velo_avg += dist/(time1);

			}
			//cout<<runs<<" %"<<endl;
		}

		dist_avg /= N_RUNS;
		velo_avg /= N_RUNS;

		cout<<"Average Distance: "<<dist_avg<<" ";
		cout<<"Average Velocity: "<<velo_avg<<" ";
		cout<<"Force: "<<force/FORCE_STEP<<" %"<<endl;

		f1<<force<<" "<<dist_avg<<endl;
		f2<<force<<" "<<velo_avg<<endl;

	}


	return 0;
}