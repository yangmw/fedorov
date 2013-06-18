// Filename: main.c
// Date created: 13 May 2013
// Last Modified: 17 Jun 2013 (16:43:34)
//
// Brief: 
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

// C Libraries
#include <math.h>
#include "vector.h"
#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Lsfit Library
#include "lib.h"
#define RMIN 0.7
#define RMAX 1.0
#define RND ((double)rand()/RAND_MAX)*(RMIN-RMAX) + RMIN  
//#define RND 1.0

double func_to_fit(double x){return 1.0 + 2.0*x + 3.0*x*x;}

double fit_func(double func(int,double), vec* c, double x){
   double s=0;
   for(int i=0; i<c->size; i++) s+= vec_get(c,i)*func(i,x);
   return s;
}
double func(int k, double x){
   switch(k){
       case 0: return 1.0; break;
       case 1: return x;   break;
       case 2: return x*x; break;
       default: {fprintf(stderr,"funs: wrong k:%d",k); return NAN;}
   }
}

int main(int argc, char** argv){
    srand(time(NULL));
    // Number of datapoints
    int n=10;
    // Allocate memory for the datapoints
    vec *x = vec_new(n);
    vec *y = vec_new(n);
    vec *dy = vec_new(n);
    // Making datapoints
    double a = -0.9;
    double b =  0.9;
    double xi,yi,dyi;
    printf("# x y dy (datapoints) \n");
    for(int i=0; i<n; i++){
	xi = a + (b-a)*i/(n-1);
	yi = func_to_fit(xi) + RND;
        dyi = RND;
    	vec_set(x, i, xi);
        vec_set(y, i, yi);
        vec_set(dy,i, dyi);            
	printf("%4g %4g %4g \n", xi,yi, dyi);
    }
    // Least squre fit qr algorithm
    int nfunc=3;
    vec* c = vec_new(nfunc);
    mat* S = mat_new(nfunc,nfunc);
    vec* dc = vec_new(nfunc);
    vec* cplus = vec_new(nfunc);
    vec* cminus = vec_new(nfunc);
    lsfit(c,S,x,y,dy,nfunc,func);
    for(int i=0; i<nfunc; i++) vec_set(dc,i,sqrt(mat_get(S,i,i)));   
    vec_memcpy(cplus,c);
    vec_memcpy(cminus,c);
    vec_add(cminus, dc, -1.0);
    vec_add(cplus,  dc, 1.0);
    // Plotting data
    int nx = 100; // Number of points
    double h = (double)(b-a)/(nx-1); //step size
    printf("\n\n"); //New block (Gnuplot)
    printf("# x F_c(x) F_c(x)-dc F_c(x)+dc \n");
    for(int i=0; i<nx; i++) {
	printf("%g %g %g %g \n", a+i*h,\
		fit_func(func, c, a+i*h),\
		fit_func(func, cminus, a+i*h),\
		fit_func(func, cplus,  a+i*h));
    }
    // Free memory
    mat_free(S);
    vec_free(c);
    vec_free(cminus);
    vec_free(cplus);
    vec_free(x);
    vec_free(y);
    vec_free(dy);

    return 0;
}
