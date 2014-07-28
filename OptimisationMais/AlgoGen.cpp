/* ----------------------------------------------------------------------------
  Algorithme génétique : croissance du maïs
  
	GAlib :
  Copyright (c) 1995-1996 Massachusetts Institute of Technology

 
---------------------------------------------------------------------------- */
#include "AlgoGen.h"

#include <ga/ga.h>
#include <ga/GARealGenome.h>
#include <ga/GARealGenome.C>

float Objective(GAGenome &);


void AlgoGen::calcul()
{

 
///////////////////////
// création des génomes
///////////////////////



// crée un génome à 33 alleles, comprise aléatoirement entre 0 et 10
	
  GARealAlleleSetArray alleles;
  for(int k=1;k<=33;k++) 
  	alleles.add(inf,sup);
  GARealGenome genome(alleles, Objective);

// paramétres de l'algorithme génétique 
 
  GAParameterList params;
  GASteadyStateGA::registerDefaultParameters(params);
  params.set(gaNnGenerations, Ngen);
  params.set(gaNpopulationSize, Npop);
  params.set(gaNscoreFrequency, 20);
  params.set(gaNflushFrequency, 200);
  params.set(gaNselectScores, (int)GAStatistics::AllScores);

// execution de l'algorithme

 	 GASteadyStateGA ga(genome);
  ga.parameters(params);
  ga.set(gaNscoreFilename, "bog.dat");
  cout << "\n execution de l'algorithme génétique  (maximise le poid de l'epi)..." << endl;
  ga.evolve();

// traitement et sauvegarde des résultats

  genome = ga.statistics().bestIndividual();
  cout << "l'algorithme a généré :\n" << endl;
  for(int i=0;i<genome.length();i++)
  { 
	cout <<  (i+1) << "  " << genome.gene(i); 
        cout << "\n";
  }
  for(int i=1;i<34;i++)
  {
	W[i]=genome.gene(i-1);
  }
 

// sauvegarde vers resultat.txt  
  if( textresult==1){
	  ofstream log("resultat.txt");
	  log << "# l'algorithme a généré :\n" << endl;
	  float sommeW=0.0;
	  for(int i=1;i<34;i++)
		sommeW+=W[i];
	  for(int i=1;i<34;i++)
	  {
		log << i << "  " << W[i];
		log << "\n";
	  }
	  objresultat->recupgenome(W);
	  log << "\n# masse de l'épi : " << objresultat->masseepi() << endl;
	  log << "\n# somme des composantes du vecteur W : " << sommeW << endl;
	  log << "\n# divergence de la meilleure population : " << ga.statistics().bestPopulation().div() << endl;
	  log << "\n# score de la meilleure population : " << ga.statistics().current() << endl;
	  log << "\n# nombre de selections effectuées : " << ga.statistics().selections() << endl;
	  log << "\n# nombre de mutations effectuées : " << ga.statistics().mutations() << endl;

  }
};



void AlgoGen::resultat()
{

  //creation du temoin
  double *Wt;
  Wt = new double[34];
  for(int i=1;i<34;i++)
  {
	Wt[i]=1.0;
  }
  Objectif *objtemoin;
  objtemoin = new Objectif();
  objtemoin->recupgenome(Wt);
   
// sauvegarde de l'évolution de la masse de l'épi dans epi.txt (et temoin dans temoin.txt -> vecteur W avec composantes égales à 1)

  ofstream epilog("epi.txt");
  epilog << "# masse de l'epi à chaque cycle : " << endl;
  for(int i=1;i<34;i++) 
	  epilog << i << "  " << objresultat->masse(i) << "  " <<  objtemoin->masse(i) << endl;
  system("gnuplot ScriptGraphe");
  delete[] Wt;
  delete objtemoin;
};


double AlgoGen::getW(int i)
{
	return W[i];
};





//fonction objectif : optimisation du poids de l'epi d'une génération à l'autre en gardant un arrosage raisonnable

float
Objective(GAGenome& g)
{
  GARealGenome& genome = (GARealGenome&)g;
  float value=0.0;
  float sommeW=0.0;
  double mepi=0.0;
  //Objectif obj;
  Objectif *obj;
  obj= new Objectif();
  double* X;
  X = new double[34];
  for(int i=1;i<34;i++)
  {
	  X[i]=genome.gene(i-1);
  }
  //obj.recupgenome(X);
  obj->recupgenome(X);
  //mepi=obj.masseepi();
  mepi=obj->masseepi();
  for(int i=0; i<genome.length(); i++)
    sommeW += genome.gene(i);
  if(sommeW>=32 & sommeW<=33)
  {
	  value+=mepi;
  }
  delete[] X;
  delete obj;
  return value;
};






