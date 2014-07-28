/*---------------------------------------------------------
 *
 *                  Particle.h
 *
 *-------------------------------------------------------*/



#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;

typedef vector<double> vec;

using namespace std;

class Particle
{
	public :
	//current position
	vec present;
	
	//best position of this particle
	vec pbest;
	
	//best position of all the particles
	vec gbest;
	
	//id number of this particle
	int pnumber;
	
	//randomising seed used in init procedure
	time_t seed;
	
	//position components are between inf and sup
	double inf;
	double sup;
	
	//current score of this particle
	double score;
	
	//best score of this particle
	double bestscore;
	
	//learning coefficients
	double c1;//historical learning
	double c2;//global learning
	
	//current velocity of this particle
	vec velocity;
	
	Particle(int pn)
	{
		c1=2;
		c2=2;
		//seed for init of this particle
		seed = time(NULL);
		pnumber = pn;
		inf = 0.6;
		sup = 1.4;
		srand(pnumber*seed);
		present.resize(34);
		//init of this particle's position
		for(int i=0;i<34;i++) 
			present[i]=inf+(sup-inf)*((double)rand()/(double)(RAND_MAX));
		pbest.resize(34);
		for(int i=0;i<34;i++)  
			pbest[i]=present[i];
		gbest.resize(34);
		for(int i=0;i<34;i++)  
			gbest[i]=0;
		velocity.resize(34);
		for(int i=0;i<34;i++) 
			velocity[i]=0;
	}
	

	~Particle()
	{
		present.clear();
		pbest.clear();
		velocity.clear();
	}
	void setscore();
	void setvelocity();
	void setposition();
	void setgbest(vec v);




};



#endif
