// Date created: 28 Apr 2013
// Last Modified: 28 Apr 2013 (23:31:28)
//
// Brief: Quadratic spline interpolation algorithm 
// Input: n points (x,y) to be interpolated
// Output: m points (z,s) for the quadratic interpolant 
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdlib.h>
#include <assert.h>
typedef struct {
	int n;
	double *x;
	double *y;
	double *b;
	double *c;
} Qspline;

int binary_search(double z, double *x, double *y, int n);

//Brief: Constructs the quadratic spline structure
Qspline* qspline_construct(int n, double *x, double *y){
	//Allocate memory for the Spline
	Qspline *S = (Qspline *)malloc(sizeof(Qspline));
	//Allocate memory for the b coefficients
	double *b = (double *)malloc(n*sizeof(double));
	//Allocate memory for the c coefficients
	double *c = (double *)malloc(n*sizeof(double));
	//Allocate memory for the copy of x values
	double *cp_x = (double*)malloc(n*sizeof(double));
	//Allocate memory for the copy of y values
	double *cp_y = (double*)malloc(n*sizeof(double));
	//Allocate memory for the p coefficients
	double p[n-1];	
	//Allocate memory for Delta x
	double dx[n-1];
	//Dummy variables
	int i;

	//Copy x to cp_x and y to cp_y
	for(i=0; i<n; i++){
		cp_x[i] = x[i];
		cp_y[i] = y[i];
	}

	//Intialize the Qspline structure S
	S->n = n; //(*S).n = n
	S->x = cp_x;
	S->y = cp_y;
	S->b = b;
	S->c = c;

	//Calculate the p coefficients and Delta x
	for(i=0; i<n-1; i++){
		dx[i] = (x[i+1]-x[i]);	
		p[i] = (y[i+1] - y[i])/dx[i];
	}

	//Forward recursion for finding the c coefficents
	c[0] = 0; //c_1 = 0
	for(i=0; i<n-2; i++){
		c[i+1] = (p[i+1]-p[i]-c[i]*dx[i])/dx[i+1];
	}

	//Backward recursion for finding the c coefficents
	c[n-2] = c[n-2]/2; // c_[n-1] = 1/2 c_[n-1]
	for(i=n-3; i>=0; i--){
		c[i] = (p[i+1]-p[i]-c[i+1]*dx[i+1])/dx[i]; 
	}

	//Calculate the b coefficients
	for(i=0; i<n-1; i++){
		b[i] = p[i] - c[i]*dx[i];
	}

	return S;
}

//Brief: Free the allocated memory
void qspline_free(Qspline *S){
	free(S->x);
	free(S->y);
	free(S->b);
	free(S->c);
	free(S);
}

//Brief: Evaluate the points z S_i(z) and place it in the correct Spline i 
double qspline_evaluate(Qspline *S, double z){	
	int i = 0; 
	double s = 0;
	double h = 0;

	//The must z value must be in the range x_0 <= z <= x_(n-1) 
	assert (z >= S->x[0] && z <= S->x[S->n-1]);
	
	//Call to the binary search algorithm
	i = binary_search(z, S->x, S->y, S->n);	
	h = z-S->x[i]; 
	s = S->y[i] + S->b[i]*h + S->c[i]*h*h;

	return s;
}


