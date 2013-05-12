// Filename: inverse.c
// Date created: 12 May 2013
// Last Modified: 13 May 2013 (00:18:36)
//
// Brief: Algorithm for calculating the inverse of a matrix
// Input: Matrix A
// Output: Inverse of Matrix A
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <matrix.h>
#include <qrlib.h>
#include <assert.h>

// Calculates the inverse of A after a QR-decomposition
void qr_inv(mat* A, const mat* Q, const mat* R){
    assert(A->row == A->col);
    qrdec(Q,R); 
    
}
