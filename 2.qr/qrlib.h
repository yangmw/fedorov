// Filename: qr.h
// Date created: 06 May 2013
// Last Modified: 12 May 2013 (23:29:28)
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

#ifndef QRLIB_H

void qrdec(mat* Q, mat* R);
void qrback(vec* x, const mat* Q, const mat* R, const vec* b);
double qr_abs_det(mat* R);


#define QRLIB_H
#endif
