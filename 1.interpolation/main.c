// Date created: 26 Apr 2013
// Last Modified: 10 May 2013 (16:05:29)
//
// Brief: main program
// Input: m points [x,y], n points for the interpolants
// Output: n points [z,s] for the interpolants 
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

// C library
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Interpolation library 
#include <intlib.h>

int main(int argc, char *argv[]){ 
	// Number of points to be fitted with spline 
	int dim = 10; 
	// Number of points for the fitted graph
	int steps = 100; 
	// Allocate memory for a vector x with all the x-coordinates
	double *x = malloc(dim*sizeof(double));
	// Allocate memory for a vector y with all the y-coordinates
	double *y = malloc(dim*sizeof(double));
	// Allocation for the points (z,s) for the interpolant
	double z,s;
	double x0, xn, h;
	/* 
	 * A. (6 points) Linear and quadratic splines 
	 */
	
	//Input n points for the interpolation 	
	printf("# x y (points)\n");
	for(int i = 0; i < dim; i++){ 
		x[i] = i + 0.5*sin(i); 
		y[i] = i + cos(i*i);
		printf("  %2.6f %2.6f \n",x[i],y[i]);
	}

	//Input m points for the interpolants
	x0 = x[0];
	xn = x[dim-1];
	h = (xn - x0)/steps; 

	//Polynomial interpolation
	s = 0;
	z = 0;
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (polynomial interpolation) \n");
	for(int i = 0; i < steps; i++){ 
		z = x0 + h*i;
		s = polinterp(z,x,y,dim);
		printf("  %2.6f %2.6f \n", z, s);
	}

	//Linear spline interpolation
	s=0;
	z=0;
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (liner spline interpolation)\n");
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = linterp(z,x,y,dim);
		printf("  %2.6f %2.6f \n", z, s);
	}
	
	//Quadratic spline interpolation 
	s=0;
	z=0;
	qspline *qs = qspline_new(dim,x,y);
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (quadratic spline interpolation)\n");
	
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = qspline_get(qs,z);
		printf("  %2.6f %2.6f \n", z, s);
	}
	/*
	 * B. (3 points) Derivatives and integrals with quadratic spline
	*/
        dim = 10;
	//Input
	fprintf(stderr, "# x y (points)\n");
	for(int i = 0 ;i<dim; i++){ 
	    x[i] = i*2*M_PI/(dim-1);
	    y[i] = sin(x[i]);
	    fprintf(stderr," %2.6f %2.6f \n", x[i], y[i]);
	}

	x0 = x[0];
	xn = x[dim-1];
	h = (xn - x0)/steps;

	//Quadratic spline interpolation 
	s=0;
	z=0;
	qs = qspline_new(dim,x,y);
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (quadratic spline interpolation)\n");
	
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = qspline_get(qs, z);
		fprintf(stderr, "  %2.6f %2.6f \n", z, s);
	}

	//Derivative of the quadratic spline interpolatio
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (derivative of the qspline)\n");
	for(int i = 0; i < steps; i++){
		//printf(stderr,"hello \n");
	    	z = x0 + h*i;
		s = qspline_deriv(qs, z);
		fprintf(stderr," %2.6f %2.6f \n", z, s);
	}

	//Free memory
	qspline_free(qs);
	free(x);
	free(y);
	fclose(stdout);
        fclose(stderr);

	return 0;
} 
