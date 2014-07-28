/*--------------------------------------------------------
 *
 *                     Swarm.cpp
 *
 *------------------------------------------------------*/


#include "Swarm.h"

using namespace std;

void Swarm::findgbest()
{
	for(int i=0;i<Npart;i++)
	{ 
		if (part[i]->score >= gbestscore)
		{
			gbestscore = part[i]->score;
			for(int j=1;j<34;j++)
				gbestposition[j]=part[i]->present[j];
		}
	}
}

void Swarm::update()
{
	for(int i=0;i<Npart;i++)
	{
		part[i]->setposition();
		part[i]->setscore();
	}
	
	this->findgbest();

	for(int i=0;i<Npart;i++) 
	{
		part[i]->setgbest(gbestposition);
		part[i]->setvelocity();
	}
}


double Swarm::getParticleCoord(int ParticleNumber, int Coord)
{
	return part[ParticleNumber]->present[Coord];
}

void Swarm::unleash()
{
	for(int i=0;i<Nit;i++)
	{
		this->update();
	}
	
	swarmresult=gbestposition;
}









		




