// Filename: inverse.c
// Date created: 12 May 2013
// Last Modified: 17 Jun 2013 (12:49:36)
//
// Brief: Algorithm for calculating the inverse of a matrix
// Input: Matrix A
// Output: Inverse of Matrix A
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <matrix.h>
#include <vector.h>
#include <assert.h>
#include <stdlib.h>

// Custom library
#include <lib.h>

// Calculates the inverse of A after a QR-decomposition
void qrinverse(mat* invA){
    // A needs to be quadratic 
    assert(invA->row == invA->col);
   
    mat* I = mat_new(invA->row, invA->col);
    mat* C = mat_new(invA->row, invA->col);
    mat* Q = mat_new(invA->row, invA->col);
    mat* R = mat_new(invA->row, invA->col);
    mat* invR = mat_new(invA->row, invA->col);

    mat_set_id(I);
 
    mat_memcpy(Q, invA);
    qrdec(Q,R); 

    vec* colx = vec_new(invA->row);
    vec* coli = vec_new(invA->row);

    for(int i=0; i<R->col; i++){
	mat_get_col(coli, I, i);
	backsub(colx, R, coli);
	mat_set_col(invR, colx, i);
    }

    mat_mul_BT(invA, invR, Q);

    // Free memory
    vec_free(colx);
    vec_free(coli);
    mat_free(invR);
    mat_free(I);
    mat_free(C);
}
