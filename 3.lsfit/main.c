// Filename: main.c
// Date created: 13 May 2013
// Last Modified: 13 May 2013 (12:47:27)
//
// Brief: 
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <vector.h>
#include <matrix.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double f(double x){return 1.0+2.0*x+3.0*x*x;}

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
    printf("# x y dy (datapoints) \n");
    for(int i=0; i<n; i++){
   	double xi = a + (b-a)*i/(n-1);
        vec_set(x, i, xi);
        vec_set(y, i, f(xi) + fRand(0.2,1.0));
        vec_set(dy,i, fRand(0.2,1.0));            
        printf("%g %g %g \n", vec_get(x,i), vec_get(y,i), vec_get(dy,i));
    }

    vec_free(x);
    vec_free(y);
    vec_free(dy);
    return 0;
}
