/* ----------------------------------------------------------------------------
  Algorithme g�n�tique : croissance du ma�s
  
	GAlib :
  Copyright (c) 1995-1996 Massachusetts Institute of Technology

 
---------------------------------------------------------------------------- */
#include <stdio.h>
#include <iostream>
#include <ga/ga.h>
#include <ga/GARealGenome.h>
#include <ga/GARealGenome.C>
#include "Objectif.h"

using namespace std;

float Objective(GAGenome &);

int main(int argc, char** argv)
{
 

//Parametrage pour obtenir un r�sultats identiques sur plusieurs execution

  unsigned int seed = 0;
  for(int ii=1; ii<argc; ii++) {
    if(strcmp(argv[ii++],"seed") == 0) {
      seed = atoi(argv[ii]);
    }
  }

 
///////////////////////
// cr�ation des g�nomes
///////////////////////



// cr�e un g�nome � 33 alleles, comprise al�atoirement entre 0 et 10
	
  GARealAlleleSetArray alleles;
  for(int k=1;k<=33;k++) 
  	alleles.add(0,10);
  GARealGenome genome(alleles, Objective);

// param�tres de l'algorithme g�n�tique 
 
  GAParameterList params;
  GASteadyStateGA::registerDefaultParameters(params);
  params.set(gaNnGenerations, 500);
  params.set(gaNpopulationSize, 110);
  params.set(gaNscoreFrequency, 10);
  params.set(gaNflushFrequency, 50);
  params.set(gaNselectScores, (int)GAStatistics::AllScores);
  params.parse(argc, argv, gaFalse);

// execution de l'algorithme
	  GASteadyStateGA ga(genome);
  ga.parameters(params);
  ga.set(gaNscoreFilename, "bog.dat");
  cout << "\n execution de ga  (maximise le poid de l'epi)..." << endl;
  ga.evolve();
  cout << "l'algorithme a g�n�r� :\n" << ga.statistics().bestIndividual() << endl;
  return 0;
}


//fonction objectif : optimisation du poids de l'epi d'une g�n�ration � l'autre en gardant un arrosage raisonnable

float
Objective(GAGenome& g)
{
  GARealGenome& genome = (GARealGenome&)g;
  float value=0.0;
  float sommeW=0.0;
  double mepi=0.0;
  double* X;
  X = new double[34];
  for(int i=;i<;i++)
  {
	X[i]=genome.gene(i);
  }
  Objectif obj;
  obj.recupgenome(X);
  mepi=obj.masseepi();
  for(int i=0; i<genome.length(); i++)
    sommeW += genome.gene(i);
  if(sommeW>=32 & sommeW<=34)
  {
	  value+=500;
  }
  value+=mepi;
  return value;
}

