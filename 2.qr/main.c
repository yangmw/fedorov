// Date created: 29 Apr 2013
// Last Modified: 13 May 2013 (09:30:48)
//
// Brief:
// Input:
// Output:
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

// C library
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <math.h>

// QR library
#include <qrlib.h>

// Utility library
#include <matrix.h>
#include <vector.h>

double in[3][3] = {
	{  1,  -1,   4},
	{  6,   1,  -1},
	{ -4,   2,  -4},
};

double inb[3] = {  1,  -1,   3};

int main (void){
    printf("Setting up Matrix A for QR-algorithm for square matrices...\n");
    int m = 3;
    int n = 3;
    int pre = 4;

    vec* b = vec_new(m);
    vec* c = vec_new(m);
    vec* x = vec_new(m);
    mat* A = mat_new(m,n);
    mat* Q = mat_new(m,m);
    mat* R = mat_new(m,n);
    mat* C = mat_new(m,n);

    //Setup matrix A
    for(int i=0; i<m; i++)
	for(int j=0; j<n; j++)
	    mat_set(A,i,j,in[i][j]); 

    printf("Matrix A: \n");
    mat_print(A, pre);
    
    //Copy Matrix A
    mat_memcpy(Q, A);

    //Setup vector b
    for(int i=0; i<m; i++)
    	vec_set(b,i,inb[i]);

    printf("Vector b: \n");
    vec_print(b, pre);

    //QR-algorithm
    qrdec(Q, R);

    printf("Matrix R: \n");
    mat_print(R, pre); 

    printf("Matrix Q: \n");
    mat_print(Q, pre);

    printf("Matrix Q' x Q = 1: \n");
    mat_mul_T(C,Q,Q);
    mat_print(C, pre);
   
    printf("Matrix A = Q x R: \n");
    mat_mul(C, Q, R);
    mat_print(C, pre);

    printf("Solving QRx = b... \n");
    qrback(x,Q,R,b); 
    printf("Vector x: \n");
    vec_print(x, pre);

    printf("Testing the solution.. Ax = b\n");
    mat_mul_vec(c,A,x);
    vec_print(c, pre);

    printf("|det(A)|:  %g \n", qr_abs_det(R));
    
    //Free memory
    mat_free(C);
    mat_free(A);
    mat_free(R);
    mat_free(Q);

    return 0;
}

