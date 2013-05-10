// Date created: 28 Apr 2013
// Last Modified: 09 May 2013 (23:56:55)
//
// Brief: Linear spline interpolation algorithm 
// Input: x[n],y[n], point z
// Output: value s  
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <assert.h> 
#include <intlib.h>

double linterp(double z, double *x, double *y, int n){
	//The must z value must be in the range x_0 <= z <= x_(n-1) 
	assert(z>=x[0] && z<=x[n-1] && n>1);

	double s = 0;
	double p = 0;
	int i = 0;

#ifdef DEBUG
	printf("Inside linterp\n");
#endif		
	//Call to the binary search algorithm 	
	i = binary_search(z, x, y, n);
	p = (y[i+1]-y[i])/(x[i+1]-x[i]);
	s = y[i] + p*(z-x[i]);
	return s;
}

