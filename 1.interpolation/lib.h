// Filename: interpolation.h
// Date created: 09 May 2013
// Last Modified: 03 Jun 2013 (16:02:08)
//
// Brief: Headerfile for all the methods for the exercise
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#ifndef LIB_H

typedef struct {
	int n;
	double *x;
	double *y;
	double *b;
	double *c;
} qspline;

typedef struct {
	int n;
	double *x;
	double *y;
	double *b;
	double *c;
	double *d;
} cspline;

cspline* cspline_new(int n, double* x, double *y);
double cspline_get(cspline* cs, double z);
double cspline_deriv(cspline* cs, double z);
double cspline_int(cspline* cs, double z);
void cspline_free(cspline* cs);

qspline* qspline_new(int n, double* x, double* y);
double qspline_get(qspline* qs, double z);
double qspline_deriv(qspline* qs, double z);
double qspline_int(qspline* qs, double z);
void qspline_free(qspline* qs);

int binary_search(double z, double* x, int n);

double linterp(double z, double* x, double* y, int n);
double polinterp(double z, double* x, double* y, int n);

#define LIB_H
#endif

