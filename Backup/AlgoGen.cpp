/*********************************************************************
 *              Algorithme génétique
 *
 *
 *********************************************************************/



#include <stdio.h>
#include <iostream>
#include <ga/ga.h>
#include <ga/GARealGenome.h>
//#include <ga/GARealGenome.C>
#include <Objectif.h>

using namespace std;


class AlgoGen{

	//Variables de l'algo
	
	float Objective(GAGenome &);
	GARealAlleleSetArray alleles;
	GARealGenome genome(alleles,Objective);
	GAParameterList params;
	GaSteadyStateGA ga(genome);
	

	//déclaration des fonctions
	public:
	AlgoGen()
	{}

	~AlgoGen()
	{}

	float Objective(GAGenome& g)
	{
		GARealGenome& genome = (GARealGenome&)g;
		float value=0.0;
                float sommeW=0.0;
                double mepi=0.0;
                Objectif obj;
	        obj.recupgenome(genome);
	        mepi=obj.masseepi();
	        for(int i=0; i<genome.length(); 
			sommeW += genome.gene(i);
		        if(sommeW>=32 & sommeW<=34)
		        {
	                	value+=500;
			}
	        value+=mepi;
		return value;



		
	}
};

int main()
{
	AlgoGen algo;
	//initialisation des alleles
	for(int k=1;k<=33;k++)
	        alleles.add(0,10);
	//mise en place de l'objectif de l'algo
	
	//initialisation des parametres de l'algo
	GASteadyStateGA::registerDefaultParameters(params);
	params.set(gaNnGenerations, 500);
	params.set(gaNpopulationSize, 110);
	params.set(gaNscoreFrequency, 10);
	params.set(gaNflushFrequency, 50);
	params.set(gaNselectScores, (int)GAStatistics::AllScores);
	params.parse(argc, argv, gaFalse);

	//execution de l'algo
	ga.parameters(params);
	ga.set(gaNscoreFilename, "bog.dat");
	cout << "\n execution de ga  (maximise le poid de l'epi)..." << endl;
	ga.evolve();
	cout << "l'algorithme a généré :\n" << ga.statistics().bestIndividual() << endl;
	return 0;
		    
}		


