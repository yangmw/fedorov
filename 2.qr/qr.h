// Filename: qr.h
// Date created: 06 May 2013
// Last Modified: 06 May 2013 (08:40:44)
//
// Brief: Headerfile to all the QR-algorithm routines
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

void qrdec(mat A, mat R);
vec qrback(const mat Q, const mat R, const vec b);
mat qrinverse(const mat A);
