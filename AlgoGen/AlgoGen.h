/* ----------------------------------------------------------------------------
  Algorithme génétique : croissance du maïs
	header  
	GAlib :
  Copyright (c) 1995-1996 Massachusetts Institute of Technology

 
---------------------------------------------------------------------------- */

#ifndef _ALGOGEN_H_
#define _AlGOGEN_H_

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Objectif.h"

using namespace std;



class AlgoGen
{
	float inf;
	float sup;
	int Ngen;
	int Npop;
	double* W;	
  	Objectif* objresultat;
	int textresult;
	public :
	AlgoGen()
	{
		inf=0.6;
		sup=1.4;
		Ngen=100;
		Npop=100;
		W = new double[34];
  		objresultat = new Objectif();
		textresult = 1; //choix de l'impression des résultats dans resultat.txt
	}
	
	AlgoGen(float borninf,float bornsup, int Ng, int Np,int textr)
	{
		inf = borninf;
		sup = bornsup;
		Ngen = Ng;
		Npop = Np;
		W = new double[34];
  		objresultat = new Objectif();
		textresult = textr%2;
	}
	
	~AlgoGen()
	{
		delete[] W;
		delete objresultat;
	}

	void calcul();
	void resultat();
	double getW(int i);
};
#endif
