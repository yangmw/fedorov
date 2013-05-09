// Filename: qr.h
// Date created: 06 May 2013
// Last Modified: 09 May 2013 (22:48:36)
//
// Brief: Headerfile to all the QR-algorithm routines
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

void qrdec(mat* Q, mat*R, mat* A);
vec qrback(const mat Q, const mat R, const vec b);
mat qrinverse(const mat A);
