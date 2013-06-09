// Filename: qrbak.c
// Date created: 12 May 2013
// Last Modified: 08 Jun 2013 (15:29:13)
//
// Brief: QR-backsubstituion Algorithm
// Solves the equation QRx = b
//
// Input: Matrix Q,R; vector b
// Output: vector x
//
// License: copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <matrix.h>
#include <assert.h>

//Brief: Solving Ux = y, U is a upper triangular matrix
void backsub(vec* x, const mat* U, const vec* b){
    double value = 0;
    int n = U->row;
    for (int i=n-1; i>=0; i--){
	vec_set(x,i,vec_get(b,i));
	for (int j=i+1; j<n; j++){
	    value = vec_get(x,i) - mat_get(U,i,j)*vec_get(x,j);
	    vec_set(x,i,value);
	}
	value = vec_get(x,i)/mat_get(U,i,i); 
	vec_set(x,i,value);
    }
}

//Brief: Main driver for solving Rx = Q'b, R is a upper triangular matrix
void qrback(vec* x, const mat* Q, const mat* R, vec* b){
    vec* c = vec_new(Q->row);
    mat_mul_vec_T(c,Q,b);

    // Rx = Q'b back-substitution
    backsub(x,R,c); 
    vec_free(c);
}





