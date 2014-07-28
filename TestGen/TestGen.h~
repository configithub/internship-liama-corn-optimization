/*---------------------------------------------------------------
 *
 *                         TESTGEN.H
 *
 *-------------------------------------------------------------*/


#ifndef _TESTGEN_H_
#define _TESTGEN_H_

#include "Matrix.h"
#include "AlgoGen.h"
using namespace std;

class TestGen
{
	int Ntest; //nombre d'algorithme génétique
	float inf;
	float sup;
	int Ngen;
	int Npop;
	matrix* W;
	
	public :
	TestGen()
	{
		Ntest=10;
		inf=0.6;
		sup=1.4;
		Ngen=100;
		Npop=100;
		W = new matrix(Ntest,34);
		Wmoy = new double[34];
		Wmax = new double[34];
	}
	TestGen(int Nt, float borninf, float bornsup, int Ng, int Np)
	{
		Ntest = Nt;
		inf = borninf;
		sup = bornsup;
		Ngen = Ng;
		Npop = Np;
		W = new matrix(Ntest,34);
		Wmoy = new double[34];
		Wmax = new double[34];
	}
	~TestGen()
	{
		delete W;
		delete[] Wmoy;
		delete[] Wmax;
	}

	double* Wmoy;
	double* Wmax;
	
	void calcul();
	matrix* getMatrixW();
	double* getWmoy();
	double* getWmax();
	void resultat();
};
#endif
