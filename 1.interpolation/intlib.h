// Filename: interpolation.h
// Date created: 09 May 2013
// Last Modified: 10 May 2013 (16:00:30)
//
// Brief: Headerfile for all the methods for the exercise
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)


#ifndef INTERLIB_H

typedef struct {
	int n;
	double *x;
	double *y;
	double *b;
	double *c;
} qspline;

qspline* qspline_new(int n, double* x, double* y);
double qspline_get(qspline* s, double z);
double qspline_deriv(qspline* s, double z);
void qspline_free(qspline* s);

int binary_search(double z, double* x, double* y, int n);

double linterp(double z, double* x, double* y, int n);
double polinterp(double z, double* x, double* y, int n);

#define INTERLIB_H
#endif

