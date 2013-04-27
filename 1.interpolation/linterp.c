// Brief: Algorithm for the linear spline interpolation 
// Input: point evaluated at z, and x and y vector for the points
// Output: value at the point z for the selected linear spline, 
// the algorithm uses bsearch to find which spline the point z belong to.
//
// Author: Yang M. Wang	
// Date: April 2013

#include <stdio.h>
#include <assert.h> 

int bsearch(double z, double* x, double* y, int n);

double linterp(double z, double *x, double *y, int n){

	// The must z must be in the range x_0 < z < x_(n-1) 
	assert(z>=x[0] && z<=x[n-1] && n>1);

	double s = 0;
	double p = 0;
	int i = 0;

#ifdef DEBUG
	printf("Inside linterp\n");
#endif		

	i = bsearch(z, x, y, n);

	//p_i = y_(i+1)-y_i/x_(i+1)-x(i) 
	p = (y[i+1]-y[i])/(x[i+1]-x[i]);

	//S_i(z) = y_i + p_i (z -x_i)
	s = y[i] + p*(z-x[i]);

	return s;
}

