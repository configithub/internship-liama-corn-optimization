/*------------------------------------------------------------
 *
 *                     Particles main.cpp
 *
 *----------------------------------------------------------*/


#include "Particle.h"
#include "Swarm.h"
#include <iostream>
#include "Objectif.h"

using namespace std;


int main()
{
	Swarm* zerg;
	zerg = new Swarm();
	double somW;
	somW = 0;
	double* result;
	result = new double[34];
	zerg->unleash();
	for(int i=1;i<34;i++)
	{
		cout << "zerg bestposition : " << zerg->swarmresult[i] << endl;
		somW+=zerg->swarmresult[i];
		result[i]=zerg->swarmresult[i];
	}
	cout << "somme W = " << somW << endl;
	Objectif* obj;
	obj = new Objectif();
	obj->recupgenome(result);
	cout << "masse epi = " << obj->masseepi() << endl;


	delete zerg;
	delete[] result;
	delete obj;
	






	
	
	/*	
	for(int i=1;i<34;i++)
	{
		cout << "zerg bestposition : " << zerg->gbestposition[i] << endl;
	}
	cout << "bestscore of the swarm: " << zerg->gbestscore << endl;
	for(int i=1;i<34;i++)
	{
		cout << "zerg present[1] = "<< zerg->part[1]->present[i] << endl;
	}
	cout << "score: " << zerg->part[1]->score << endl;

	for(int i=1;i<34;i++)
	{
		cout << "zerg velocity[1] = "<< zerg->part[1]->velocity[i] << endl;
	}
	*/
	return 0;
}
