// Date created: 26 Apr 2013
// Last Modified: 10 Jun 2013 (00:41:32)
//
// Brief: Main program
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
#include <lib.h>
#define M_PI 3.14159265358979323846

int main(int argc, char *argv[]){ 
	// Number of points to be fitted with a given spline 
	int dim = 10; 
	// Number of points for the fitted graph
	int steps = 100; 
	// Allocate memory for a vector x with all the x-coordinates
	double *x1 = malloc(dim*sizeof(double));
	double *x2 = malloc(dim*sizeof(double));
	// Allocate memory for a vector y with all the y-coordinates
	double *y1 = malloc(dim*sizeof(double));
	double *y2 = malloc(dim*sizeof(double));
	// Allocation for the points (z,s) for the interpolant
	double z,s;
	// Allocation of step variables
	double x0, xn, h;
	
	/* 
	 * A. (6 points) Linear and quadratic splines 
	 */
	
	// Input n points for the interpolation 	
	printf("# x y (points)\n");
	for(int i = 0; i < dim; i++){ 
		x1[i] = i + 0.5*sin(i); 
		y1[i] = i + cos(i*i);
		printf("  %2.6f %2.6f \n",x1[i],y1[i]);
	}
	// Calculate m points for the interpolants
	x0 = x1[0];
	xn = x1[dim-1];
	h = (xn - x0)/steps;

	// Linear spline interpolation
	s=0;
	z=0;
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (liner spline interpolation)\n");
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = linterp(z,x1,y1,dim);
		printf("  %2.6f %2.6f \n", z, s);
	}
	// Quadratic spline interpolation 
	s=0;
	z=0;
	qspline *qs = qspline_new(dim,x1,y1);
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (quadratic spline interpolation)\n");
	
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = qspline_get(qs,z);
		printf("  %2.6f %2.6f \n", z, s);
	}
	/*
	 * B. (3 points) derivatives and integrals with quadratic spline
	*/
	
	//Input for the derivatives and integrals
	fprintf(stderr, "# x y (points)\n");
	for(int i = 0 ;i<dim; i++){ 
	    x2[i] = i*2*M_PI/(dim-1);
	    y2[i] = sin(x2[i]);
	    fprintf(stderr," %2.6f %2.6f \n", x2[i], y2[i]);
	}
	x0 = x2[0];
	xn = x2[dim-1];
	h = (xn - x0)/steps;
	
	// Quadratic spline interpolation 
	s=0;
	z=0;
	qs = qspline_new(dim,x2,y2);
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (quadratic spline interpolation)\n");
	
	for(int i = 0; i < steps; i++){
		z = x0 + h*i;
		s = qspline_get(qs, z);
		fprintf(stderr, "  %2.6f %2.6f \n", z, s);
	}
	
	// Derivative of the quadratic spline interpolation
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (derivative of the quadratic spline)\n");
	for(int i = 0; i < steps; i++){
	    	z = x0 + h*i;
		s = qspline_deriv(qs, z);
		fprintf(stderr," %2.6f %2.6f \n", z, s);
	}
	
	// Integration the quadratic spline interpolation
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (integration of the quadratic spline)\n");
	for(int i = 0; i < steps; i++){
	    	z = x0 + h*i;
		s = qspline_int(qs, z);
		fprintf(stderr," %2.6f %2.6f \n", z, s);
	}

	/*
	 * C. (1 point) Derivatives and integrals with cubic spline
	 */

	// Cubic spline interpolation with x and y values from A.
	s=0;
	z=0;
	x0 = x1[0];
	xn = x1[dim-1];
	h = (xn - x0)/steps;
	cspline* cs = cspline_new(dim,x1,y1);
	fprintf(stdout, "\n\n"); //New block (Gnuplot)
	fprintf(stdout, "# x y (cubic spline interpolation)\n");
	for(int i = 0; i < steps; i++){
	    z = x0 + h*i;
	    s = cspline_get(cs, z);
	    fprintf(stdout," %2.6f %2.6f \n", z, s);
	}

	// Derivative of the cubic spline interpolation with x,y values from B.
	s=0;
	z=0;
	x0 = x2[0];
	xn = x2[dim-1];
	h = (xn - x0)/steps;
	cs = cspline_new(dim,x2,y2);
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (derivative of the cubic spline)\n");
	for(int i = 0; i < steps; i++){
	    z = x0 + h*i;
	    s = cspline_deriv(cs, z);
	    fprintf(stderr," %2.6f %2.6f \n", z, s);
	}

	// Integration of the cubic spline interpolation with x,y values from B.
	fprintf(stderr, "\n\n"); //New block (Gnuplot)
	fprintf(stderr, "# x y (derivative of the cubic spline)\n");
	for(int i = 0; i < steps; i++){
	    z = x0 + h*i;
	    s = cspline_int(cs, z);
	    fprintf(stderr," %2.6f %2.6f \n", z, s);
	}

	// Free memory
	qspline_free(qs);
	cspline_free(cs);
	free(x1);
	free(x2);
	free(y1);
	free(y2);
	fclose(stdout);
        fclose(stderr);

	return 0;
} 
