/*---------------------------------------------------------
 *
 *                  Particle.cpp
 *
 *-------------------------------------------------------*/



#include "Particle.h"
#include "Objectif.h"
#include <cstdlib>

typedef vector<double> vec;

void Particle::setscore()
{
	score = 0;
	
	double sompresent;
	sompresent = 0;
	for(int i=1;i<34;i++) 
		sompresent += present[i];
//	if (sompresent >= 32 & sompresent <= 33) 
	if ( sompresent <= 33) 
	{
		double* W;
		W = new double[34];
		for(int i=1;i<34;i++) 
			W[i]=present[i];
		Objectif* obj;
		obj = new Objectif();
		obj->recupgenome(W);
		score = obj->masseepi();
		delete[] W;
		delete obj;
	}
	else
	{
		score = 0;
	}
	if(score>=bestscore)
	{
		bestscore = score;
		for(int i=1;i<34;i++) 
			pbest[i]=present[i];
	}
	
}

void Particle::setposition()
{
	for(int i=1;i<34;i++) 
		if (present[i]+velocity[i]>=inf)
			present[i]+=velocity[i];
		else
			present[i]=inf;
}

void Particle::setgbest(vec v)
{
	for(int i=1;i<34;i++) 
		gbest[i] = v[i];
}

void Particle::setvelocity()
{
	//seed for r1 & r2
	time_t seedvelo;
	srand(seedvelo);
	double r1;
	r1 = ((double)rand()/(double)(RAND_MAX));
	double r2;
	r2 = ((double)rand()/(double)(RAND_MAX));
	//r1 & r2 are random number in [0;1]
	for(int i=1;i<34;i++)
		velocity[i]+=c1*r1*(pbest[i]-present[i])+c2*r2*(gbest[i]-present[i]);
}


	
