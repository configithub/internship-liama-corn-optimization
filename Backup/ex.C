/* ----------------------------------------------------------------------------
  ex21.C
  mbwall 1jan96
  Copyright (c) 1995-1996 Massachusetts Institute of Technology

 DESCRIPTION:
   This example illustrates various uses of the AlleleSet in concert with the
ArrayAlleleGenome.  In particular, we use the RealGenome to show how you can
use the enumerated and bounded types of allele sets.
   You can define one allele set for an entire array, or you can define one
allele set for each element in the array.  The constructor that you use to 
create the array determines which behaviour you'll get.
---------------------------------------------------------------------------- */
#include <stdio.h>
#include <iostream>
#include <ga/ga.h>
#include <ga/GARealGenome.h>
#include <ga/GARealGenome.C>

float Objective4(GAGenome &);

int
main(int argc, char** argv)
{
  cout << "Example 21\n\n";
  cout << "This example shows various uses of the allele set object\n";
  cout << "in combination with the real number genome.\n\n"; cout.flush();

// See if we've been given a seed to use (for testing purposes).  When you
// specify a random seed, the evolution will be exactly the same each time
// you use that seed number.

  unsigned int seed = 0;
  for(int ii=1; ii<argc; ii++) {
    if(strcmp(argv[ii++],"seed") == 0) {
      seed = atoi(argv[ii]);
    }
  }

// First make a bunch of genomes.  We'll use each one in turn for a genetic
// algorithm later on.  Each one illustrates a different method of using the
// allele set object.  Each has its own objective function.


// This genome is created using an array of allele sets.  This means that each
// element of the genome will assume a value in its corresponding allele set.
// For example, since the first allele set is [0,10], the first element of the
// genome will be in [0,10].  Notice that you can add allele sets in many other
// ways than those shown.

  GARealAlleleSetArray alleles4;
  for(int j=1;j<34;j++)
  { 
  	alleles4.add(0,10);
  }
  GARealGenome genome4(alleles4, Objective4);


// Now that we have the genomes, create a parameter list that will be used for
// all of the genetic algorithms and all of the genomes.

  GAParameterList params;
  GASteadyStateGA::registerDefaultParameters(params);
  params.set(gaNnGenerations, 500);
  params.set(gaNpopulationSize, 110);
  params.set(gaNscoreFrequency, 10);
  params.set(gaNflushFrequency, 50);
  params.set(gaNselectScores, (int)GAStatistics::AllScores);
  params.parse(argc, argv, gaFalse);


// Now do a genetic algorithm for each one of the genomes that we created.


  GASteadyStateGA ga4(genome4);
  ga4.parameters(params);
  ga4.set(gaNscoreFilename, "bog4.dat");
  cout << "\nrunning ga number 4 (maximize each gene)..." << endl;
  ga4.evolve();
  cout << "the ga generated:\n" << ga4.statistics().bestIndividual() << endl;

  return 0;
}
 



// This objective function tries to maximize the occurance of the first and
// fourth alleles.  It tries to put the first allele in the even elements and
// the fourth allele in the odd elements.



// This objective tries to maximize each element in the genome.

float
Objective4(GAGenome& g)
{
  GARealGenome& genome = (GARealGenome&)g;
  float value=0.0;
  for(int i=0; i<genome.length(); i++)
    value += genome.gene(i);
  return value;
}
