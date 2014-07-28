/*------------------------------------------------------------
 *
 *                     Particles main.cpp
 *
 *----------------------------------------------------------*/


#include "Swarm.h"
#include <iostream>
#include "TestGen.h"
#include "Objectif.h"
#include "Calculst.h"
#include <fstream>
using namespace std;


int main()
{

//ParticleSwarm



	
	Swarm* pswarm;
	pswarm = new Swarm(100,1000);
	double PSsomW;
	PSsomW = 0;
	double* PSresult;
	PSresult = new double[34];
	double* PSmasse;
	PSmasse = new double[34];
	pswarm->unleash();
	for(int i=1;i<34;i++)
	{
		cout << "pswarm bestposition : " << i << "  "  << pswarm->swarmresult[i] << endl;
		PSsomW+=pswarm->swarmresult[i];
		PSresult[i]=pswarm->swarmresult[i];
	}
	cout << "Particle swarm : somme W = " << PSsomW << endl;
	Objectif* obj;
	obj = new Objectif();
	obj->recupgenome(PSresult);
	for(int i=1;i<34;i++) 
		PSmasse[i]=obj->masse(i);
	cout << "Particle swarm : masse epi = " << obj->masseepi() << endl;



//AlgoGen


//batterie de 10 algorithmes génétiques
	/*
	TestGen* algogen;
	algogen = new TestGen();
	double AGsomW;
	AGsomW=0;
	double* AGresult;
	AGresult = new double[34];
	double* AGmasse;
	AGmasse = new double[34];
	algogen->calcul();
	for(int i=1;i<34;i++)
	{
		AGsomW+=algogen->getWmoy()[i];
		AGresult[i]=algogen->getWmoy()[i];
		cout << "algogen best genome : " << i << "  " << AGresult[i] << endl;
	}
	cout << "Algorithme genetique : somme W = " << AGsomW << endl;
	obj->recupgenome(AGresult);
	for(int i=1;i<34;i++) 
		AGmasse[i]=obj->masse(i);
	cout << "Algorithme genetique : masse epi = " << obj->masseepi() << endl;
	*/


//algorithme générique simple
	

	AlgoGen* alg;
	alg = new AlgoGen();
	double AGsomW;
	AGsomW=0;
	double* AGresult;
	AGresult = new double[34];
	double* AGmasse;
	AGmasse = new double[34];
	alg->calcul();
	for(int i=1;i<34;i++)
	{
		AGresult[i] = alg->getW(i);
		AGsomW+=AGresult[i];
	}
	obj->recupgenome(AGresult);
	for(int i=1;i<34;i++) 
		AGmasse[i]=obj->masse(i);
	cout << "Algorithme genetique : masse epi = " << obj->masseepi() << endl;

	



//Penalisation


	
	double* Pmasse;
	Pmasse = new double[34];
	double* Presult;
	Presult = new double[34];
	double PsomW;
	PsomW = 0;
	Calculs aaa;
	aaa.vdem();
	int iter;
	int iiii;
	
	for(iter=0;iter<47;iter++)
	{
		aaa.compile_gradient(iter);
		if(iter==46)
		{
			for (iiii=1;iiii<34;++iiii)
			{
				Pmasse[iiii] =  aaa.masse(iiii);
				Presult[iiii]= aaa.W[iiii];
				PsomW += aaa.W[iiii];
			}
		}        
		aaa.algo_grad(iter);
		//system("pause");
	}


//Temoin


	double* Tresult;
	Tresult = new double[34];
	double* Tmasse;
	Tmasse = new double[34];

	for(int i=1;i<34;i++) 
		Tresult[i]=1;
	
	obj->recupgenome(Tresult);
	
	for(int i=1;i<34;i++) 
		Tmasse[i]=obj->masse(i);

	

//Masse.txt

	ofstream log("masse.txt");
	log << "#Masse de l'épi à chaque cycle pour chaque méthode d'optimisation" << endl << endl;
	log << "#Cycle: Temoin: Penalisation: AlgoGen: PSwarm: " << endl;
	for(int i=1;i<34;i++)  
		log << i << "  " << Tmasse[i] << "  " << Pmasse[i] << "  " << AGmasse[i] << "  " << PSmasse[i] << endl;
	log << endl;
	log << "#somme des composantes des vecteurs W obtenus pour chaque méthode : " << endl;
	log << "#Temoin: Penalisation: AlgoGen: PSwarm: " << endl;
	log << "33" << "  " << PsomW << "  " << AGsomW << "  " << PSsomW << endl;
	
	


//Tracé du graphe
	
	system("gnuplot ScriptGraphe");
	
	delete pswarm;
	delete[] PSresult;
	delete[] PSmasse;
	//delete algogen;
	delete alg;
	delete[] AGresult;
	delete[] AGmasse;
	delete[] Pmasse;
	delete[] Presult;
	delete obj;
	






	
	
	return 0;
}
