/*--------------------------------------------------------
 *
 *                     Swarm.h
 *
 *------------------------------------------------------*/

#ifndef _SWARM_H_
#define _SWARM_H_

#include "Particle.h"
#include <iostream>

using namespace std;

typedef vector<double> vec;

class Swarm
{
	public :
	
	//number of particles
	int Npart;

	//number of iterations
	int Nit;

	//best score ever achieved by any particle of the swarm
	double gbestscore;
	
	//Particle* part;
	vector<Particle*> part;
	
	vec gbestposition;
	
	vec swarmresult;
	
	Swarm()
	{
		Npart=100;
		Nit=100;
		gbestscore=0;
		gbestposition.resize(34);
		swarmresult.resize(34);
		part.resize(Npart);
		for(int i=0;i<Npart;i++)  
		{
			part[i] = new Particle(i);
			part[i]->setscore();
		}
		this->findgbest();
		for(int i=0;i<Npart;i++) 
		{
			part[i]->setgbest(gbestposition);
			part[i]->setvelocity();
		}
	}
	Swarm(int Np, int Ni)
	{
		Npart=Np;
		Nit=Ni;
		gbestscore=0;
		gbestposition.resize(34);
		swarmresult.resize(34);
		part.resize(Npart);
		for(int i=0;i<Npart;i++)  
		{
			part[i] = new Particle(i);
			part[i]->setscore();
		}
		this->findgbest();
		for(int i=0;i<Npart;i++) 
		{
			part[i]->setgbest(gbestposition);
			part[i]->setvelocity();
		}
	}
	~Swarm()
	{
		part.clear();
		gbestposition.clear();
		swarmresult.clear();
	}

	void update();
	void findgbest();
	void unleash();
	double getParticleCoord(int ParticleNumber, int Coord);
};
#endif
