// Date created: 26 Apr 2013
// Last Modified: 27 Apr 2013 (19:27:53)
//
// Brief: main program
// Input: m points [x,y], n points for the interpolants
// Output: n points [z,s] for the interpolants 
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double linterp(double z, double *x, double *y, int n);
double polinterp(double z, double *x, double *y, int n);

int main(int argc, char *argv[]){ 

	//Number of points to be fitted ss
	int dim = 10; 
	//Number of points for the fitted graph
	int steps = 500; 
	// Allocate memory for a vector x with all the x-coordinates
	double *x = malloc(dim*sizeof(double));
	// Allocate memory for a vector y with all the y-coordinates
	double *y = malloc(dim*sizeof(double));

	int i;

	//Input n points for the interpolation 	
	printf("# x y (points)\n");
	for(i = 0; i < dim; i++){ 
		x[i] = i + 0.5*sin(i); 
		y[i] = i + cos(i*i);
		printf("  %2.6f %2.6f \n",x[i],y[i]);
	}

	//Input m points for the interpolants
	double z = 0;
	double s = 0;

	double x0 = x[0];
	double xn = x[dim-1];
	double h = (xn - x0)/steps; 

	#ifdef DEBUG
	printf("End input data\n");
	#endif

	//Polynomial interpolation
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (polynomial interpolation) \n");
	for(i = 0; i < steps; i++){ 
		z = x0 + h*i;
		s = polinterp(z,x,y,dim);
		printf("  %2.6f %2.6f \n", z, s);
	}

	s=0;
	z=0;

	#ifdef DEBUG
	printf("End polinterp \n");
	#endif

	//Linear spline interpolation 
	printf("\n\n"); //New block (Gnuplot)
	printf("# x y (liner spline interpolation)\n");
	for(i = 0; i < steps; i++){
		z = x0 + h*i;
		s = linterp(z,x,y,dim);
		printf("  %2.6f %2.6f \n", z, s);

		#ifdef DEBUG
		printf("z=%g s=%g \n", z, s);
		#endif
	}

	#ifdef DEBUG
	printf("End linterp \n");
	#endif

	//Free memory
	free(x);
	free(y);

	#ifdef DEBUG
	printf("End free memory \n");
	#endif

	fclose(stdout);
	return 0;
} 
