/*--------------------------------------------
 * 
 *            ALgoGen Main                  
 *
 *------------------------------------------*/

#include "AlgoGen.h"

int main()
{
	AlgoGen* alg;
	alg = new AlgoGen();
	alg->calcul();
	alg->resultat();
	delete alg;
  	return 0;
};

