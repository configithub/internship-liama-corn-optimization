/*--------------------------------------------------------------------------
 *
 *                            MATRIX.H
 *
 *------------------------------------------------------------------------*/


#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>

using namespace std;

class matrix
{

	vector< vector<double> > v2d;
	
	public :

	matrix(int ii, int jj)
	{
		v2d.resize(ii);
		for(int k=0;k<v2d.size();k++) 
			v2d[k].resize(jj);
		
		for(int iii=0;iii<v2d.size();iii++)
		        for(int jjj=0;jjj<v2d[iii].size();jjj++)
				 v2d[iii][jjj] = 0;
	}
	~matrix()
	{
		v2d.clear();
	}
	void setij(int ii, int jj, double value)
	{
		v2d[ii][jj]=value;
	}

	double getij(int ii, int jj)
	{
		return v2d[ii][jj];	
	}
		
};	
		

#endif
