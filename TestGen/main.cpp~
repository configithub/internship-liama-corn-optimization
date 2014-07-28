/*-------------------------------------
 *
 *           TestGen main
 *
 *-----------------------------------*/




#include "TestGen.h"
#include "Matrix.h"


double maximumValue(double* array,int length)
{
	     double max = array[0];

	     for(int i = 1; i<length; i++)
	     {				     
		     
	        if(array[i] > max)
			max = array[i];
	     }
	     
	     return max;     
}




int sizarray(double* array)
{
	int length = sizeof(array);
	return length;
}

int main()
{
	TestGen* test;
	test = new TestGen();
	test->calcul();

	cout << endl;
	cout << "W moyen : " << endl;
	cout << endl;
	for(int i=1;i<34;i++) 
		cout << i << "  " << test->getWmoy()[i] << endl;
	
	cout << endl;
	cout << "W max : " << endl;
	cout << endl;
	for(int i=1;i<34;i++) 
		cout << i << "  " << test->getWmax()[i] << endl;
	test->resultat();
	delete test;
	return 0;
}

