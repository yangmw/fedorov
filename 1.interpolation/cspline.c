// Filename: cspline.c
// Date created: 16 May 2013
// Last Modified: 06 Jun 2013 (17:18:49)
//
// Brief: Cubic spline interpolation algorithm 
// 
// Input: n points (x,y) to be interpolated
// Output: m points (z,s) for the quadratic interpolant 
//
// License: copyleft
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lib.h>

cspline* cspline_new(int n, double* x, double* y) {
    // Allocate memory for the type cspline 
    cspline* cs = (cspline*)malloc(sizeof(cspline));
    // Allocate memory for the b coefficients
    double* b = (double*)malloc(n*sizeof(double));
    // Allocate memory for the c coefficients
    double* c = (double*)malloc(n*sizeof(double));
    // Allocate memomry for the d coefficients
    double* d = (double*)malloc(n*sizeof(double));
    // Allocate memory for the copy of x values
    double* cp_x = (double*)malloc(n*sizeof(double));
    // Allocate memory for the copy of y values
    double* cp_y = (double*)malloc(n*sizeof(double));
    // Allocate memory for the dx values
    double* h = (double*)malloc((n-1)*sizeof(double));
    // Allocate memory for the p coefficients
    double* p = (double*)malloc((n-1)*sizeof(double));	
    // Dummy variables
    int i;
    // Copy x to cp_x and y to cp_y
    for (i=0; i<n; i++) {
	cp_x[i] = x[i];
	cp_y[i] = y[i];
    }
    // Intialize the qspline structure S
    cs->n = n; //Syntatic sugar: (*S).n = n
    cs->x = cp_x;
    cs->y = cp_y;
    cs->b = b;
    cs->c = c;
    cs->d = d;
    // Calculate the p and Delta x coefficients
    for (i=0; i<n-1; i++) {
	h[i] = x[i+1]-x[i];	
	p[i] = (y[i+1] - y[i])/h[i];
    }
    // Allocate memory for matrix elements
    double* D = malloc(n*sizeof(double));
    double* Q = malloc((n-1)*sizeof(double));
    double* B = malloc(n*sizeof(double));
    // Initialize the matrix: Natural conditions (Eq. 17) 
    D[0] = 2.0;
    D[n-1] = 2.0;
    Q[0] = 1.0;
    B[0] = 3.0*p[0];
    B[n-1] = 3.0*p[n-2];  
    // Create the upper triangular matrix (Eq. 22-24)
    for (int i=0; i<n-2; i++) {
	Q[i+1] = h[i]/h[i+1];
	D[i+1] = 2.0*Q[i+1]+2.0;
	B[i+1] = 3.0*(p[i]+p[i+1]*Q[i+1]);
    }  

    //for (int i=1; i<n-1; i++) {
    //Q[i] = h[i-1]/h[i];
    //D[i] = 2.0*Q[i]+2.0;
    //B[i] = 3.0*(p[i-1]+p[i]*Q[i]);
    //}  
    // Solve the system using Gauss-elimintation (Eq. 26-27)
    for (int i=1; i<n; i++) {
	D[i] = D[i] - Q[i-1]/D[i-1];
	B[i] = B[i] - B[i-1]/D[i-1];
    }
    // Find the b-coefficients using Back-substitution (Eq. 28)
    b[n-1] = B[n-1]/D[n-1];
    for (int i=n-2; i>=0; i--) {
	b[i] = (B[i]-Q[i]*b[i+1])/D[i];
    }
    // Find the c and d-coefficients (Eq. 19)
    for (int i=0; i<n-1; i++) {
	c[i] = (-2.0*b[i]-b[i+1]+3.0*p[i])/h[i];
	d[i] = (b[i]+b[i+1]-2.0*p[i])/(h[i]*h[i]);
    }
    // Free memory
    free(h);
    free(p);
    free(B);
    free(D);
    free(Q);
    return cs;
}
// Brief: This function finds i using binary search on z
// and evalutes S_i(z)
double cspline_get(cspline *cs, double z) {
    int i = binary_search(z, cs->x, cs->n);	
    double h = z-cs->x[i];
    return cs->y[i]+cs->b[i]*h+cs->c[i]*h*h+cs->d[i]*h*h*h;
}
//Brief: This function finds i using binary search 
// and evaluates the derivate of S_i(z)
double cspline_deriv(cspline *cs, double z) {
    int i = binary_search(z, cs->x, cs->n);
    double h = z-cs->x[i];
    return cs->b[i]+2.0*cs->c[i]*h+3.0*cs->d[i]*h*h;
}
// Brief: This function finds i using binary search on z
// and evaluates the integral of S_i(z)
double cspline_int(cspline* cs, double z){
    int i = binary_search(z, cs->x, cs->n);
    double sum = 0;
    double dx = 0;
    for (int j=0; j<i; j++){
	dx = cs->x[j+1]-cs->x[j]; 
	sum += cs->y[j]*dx + cs->b[j]*dx*dx/2 \
	       + cs->c[j]*pow(dx,3)/3.0 + cs->d[j]*pow(dx,4)/4.0;
    }
    double h = z - cs->x[i];
    return sum + cs->y[i]*h + cs->b[i]*h*h/2 \
	+ cs->c[i]*pow(h,3)/3.0 + cs->d[i]*pow(h,4)/4.0;
}
//Brief: Free allocated memory
void cspline_free(cspline* cs) {
    free(cs->x);
    free(cs->y);
    free(cs->b);
    free(cs->c);
    free(cs);
}

