/*---------------------------------------------------------------
 *
 *                         TESTGEN.CPP
 *
 *-------------------------------------------------------------*/

#include "TestGen.h"



void TestGen::calcul()
{
	AlgoGen* alg;
	alg = new AlgoGen(inf,sup,Ngen,Npop,0);
	for(int i=0;i<Ntest;i++)
	{ 
		alg->calcul();
		for(int j=0;j<34;j++)
		{
			W->setij(i,j,alg->getW(j));
		}
	}
	delete alg;
}


matrix* TestGen::getMatrixW()
{
	return W;
}


double* TestGen::getWmoy()
{
	for(int j=0;j<34;j++) 
		Wmoy[j]=0;
	for(int j=0;j<34;j++)
	{
		for(int i=0;i<Ntest;i++)
		{
			Wmoy[j]+=W->getij(i,j);
		}
		Wmoy[j]=Wmoy[j]/Ntest;
	}
	return Wmoy;
}


int maximumIndex(double* array,int length)
{
	     double max = array[0];
	     int maxindex = 0;

	     for(int i = 1; i<length; i++)
	     {				     
		     
	        if(array[i] > max)
		{
			max = array[i];
			maxindex = i;
		}
	     }
	     
	     return maxindex;     
}


double* TestGen::getWmax()
{
	for(int j=0;j<34;j++) 
		Wmax[j]=0;
	Objectif* obj;
	obj = new Objectif();
	double* m;
	m = new double[Ntest];
	double* Wo;
	Wo = new double[34];
	for(int i=0;i<Ntest;i++)
	{
		for(int j=0;j<34;j++)
		{
			Wo[j]=W->getij(i,j);
		}
		obj->recupgenome(Wo);
		m[i]=obj->masseepi();
	}
	int maxm;
	maxm=maximumIndex(m,Ntest);
	for(int j=0;j<34;j++)
	{ 	
		Wmax[j]=W->getij(maxm,j);
	}
	delete[] m;
	delete[] Wo;
	delete obj;
	return Wmax;
}

void TestGen::resultat()
{
	ofstream results("resultat.txt");
	results << "Le test de " << Ntest << " algorithmes génétiques a généré : "<<endl;
	results << "cylce:  Wmoy:  Wmax:  "<<endl;
	for(int i=1;i<34;i++) 
		results << i << "  " << Wmoy[i] << Wmax[i] << endl;
	

	ofstream epilog("epi.txt");
	Objectif* objmoy;
	objmoy = new Objectif();
	objmoy->recupgenome(getWmoy());
	Objectif* objmax;
	objmax = new Objectif();
	objmax->recupgenome(getWmax());
	Objectif* objtemoin;
	objtemoin = new Objectif();
	double* Wt;
	Wt = new double[34];
	for(int i=1;i<34;i++) 
		Wt[i]=1;
	objtemoin->recupgenome(Wt);
	epilog << "masses de l'épi à chaque cycle pour Wmoy et Wmax obtenus à l'aide de TestGen sur " << Ntest << " algorithmes génétiques." << endl;
	epilog << "cycle:  Wmoy:  Wmax:  temoin: " << endl;
	for(int i=1;i<34;i++)
		epilog << i << "  " << objmoy->masse(i) << "  " << objmax->masse(i) << "  " << objtemoin->masse(i) << endl;
	system("gnuplot ScriptGraphe");
	delete[] Wt;
	delete objtemoin;
	delete objmax;
	delete objmoy;
}
	
	
