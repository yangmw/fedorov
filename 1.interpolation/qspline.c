// Date created: 28 Apr 2013
// Last Modified: 21 May 2013 (15:13:33)
//
// Brief: Quadratic spline interpolation algorithm 
// Input: n points (x,y) to be interpolated
// Output: m points (z,s) for the quadratic interpolant 
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <intlib.h>

// Brief: Allocate memory and construct the quadratic spline
qspline* qspline_new(int n, double* x, double* y){
    // Allocate memory for the type qspline
    qspline* qs = (qspline*)malloc(sizeof(qspline));
    // Allocate memory for the b coefficients
    double* b = (double*)malloc(n*sizeof(double));
    // Allocate memory for the c coefficients
    double* c = (double*)malloc(n*sizeof(double));
    // Allocate memory for the copy of x values
    double* cp_x = (double*)malloc(n*sizeof(double));
    // Allocate memory for the copy of y values
    double* cp_y = (double*)malloc(n*sizeof(double));
    // Allocate memory for the dx values
    double* dx = (double*)malloc((n-1)*sizeof(double));
    // Allocate memory for the p coefficients
    double p[n-1];	
    // Dummy variables
    int i;
    // Copy x to cp_x and y to cp_y
    for(i=0; i<n; i++){
	cp_x[i] = x[i];
	cp_y[i] = y[i];
    }
    // Intialize the qspline structure S
    qs->n = n; //(*S).n = n
    qs->x = cp_x;
    qs->y = cp_y;
    qs->b = b;
    qs->c = c;
    // Calculate the p coefficients and Delta x
    for(i=0; i<n-1; i++){
	dx[i] = x[i+1]-x[i];	
	p[i] = (y[i+1] - y[i])/dx[i];
    }
    // Forward recursion for finding the c coefficents
    c[0] = 0; //c_1 = 0
    for(i=0; i<n-2; i++)
	c[i+1] = (p[i+1]-p[i]-c[i]*dx[i])/dx[i+1];
    // Backward recursion for finding the c coefficents
    c[n-2] = c[n-2]/2; // c_[n-1] = 1/2 c_[n-1]
    for(i=n-3; i>=0; i--)
	c[i] = (p[i+1]-p[i]-c[i+1]*dx[i+1])/dx[i]; 
    // Calculate the b coefficients
    for(i=0; i<n-1; i++)
	b[i] = p[i] - c[i]*dx[i];
    return qs;
}
// Brief: Free allocated memory
void qspline_free(qspline* qs){
    free(qs->x);
    free(qs->y);
    free(qs->b);
    free(qs->c);
    free(qs);
}
// Brief: This function finds i using binary search 
// and evalutes S_i(z)
double qspline_get(qspline* qs, double z){	
    // The must z value must be in the range x_0 <= z <= x_(n-1) 
    assert (z >= qs->x[0] && z <= qs->x[qs->n-1]);

    int i = binary_search(z, qs->x, qs->n);	
    double h = z-qs->x[i]; 
    return qs->y[i] + qs->b[i]*h + qs->c[i]*h*h;
}
// Brief: This function finds i using binary search on z
// and evalutes the derivative of S_i(z)
double qspline_deriv(qspline* qs, double z){
    int i = binary_search(z, qs->x, qs->n);
    double h = z-qs->x[i]; 
    return qs->b[i] + 2.0*qs->c[i]*h;  
}
// Brief: This function finds i using binary search on z
// and evaluates the integral of S_i(z)
double qspline_int(qspline* qs, double z){
    int i = binary_search(z, qs->x, qs->n);
    double sum = 0;
    double dx = 0;
    for (int j=0; j<i; j++){
	dx = qs->x[j+1]-qs->x[j]; 
	sum += qs->y[j]*dx + 0.5*qs->b[j]*dx*dx \
	      + qs->c[j]*pow(dx,3)/3;
    }
    double h = z - qs->x[i];
    return sum + qs->y[i]*h+0.5*qs->b[i]*h*h \
    	+ (1.0/3.0)*qs->c[i]*h*h*h;
}
