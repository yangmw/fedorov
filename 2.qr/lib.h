// Filename: qr.h
// Date created: 06 May 2013
// Last Modified: 08 Jun 2013 (15:53:29)
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

//Include garbage collector
//#include <gc.h>

#ifndef LIB_H

void backsub(vec* x, const mat* U, const vec* b);
void qrdec(mat* Q, mat* R);
void qrback(vec* x, const mat* Q, const mat* R, const vec* b);
void qr_inv(mat* IA);
double qr_abs_det(mat* R);
void title(char *s);

#define LIB_H
#endif
