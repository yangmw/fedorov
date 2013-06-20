// Filename: qr.h
// Date created: 06 May 2013
// Last Modified: 17 Jun 2013 (12:49:41)
//
// Brief: Headerfile to all the QR-algorithm routines
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)
#include <matrix.h>
#include <vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_cblas.h>

//Include garbage collector
//#include <gc.h>

#ifndef LIB_H

void backsub(vec* x, const mat* U, const vec* b);
void qrdec(mat* Q, mat* R);
void qrback(vec* x, const mat* Q, const mat* R, const vec* b);
void qrinverse(mat* IA);
double qr_abs_det(mat* R);
void title(char *s);
void mat_print_gsl(gsl_matrix* A_gsl, const int pre);
void vec_print_gsl(gsl_vector* v_gsl, int precision);
double vec_diff_gsl(const gsl_vector* v, const gsl_vector* w);
double mat_diff(const mat* A, const mat* B);
double vec_diff(const vec* u, const vec* v);


#define LIB_H
#endif
