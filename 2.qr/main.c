// Date created: 29 Apr 2013
// Last Modified: 09 May 2013 (23:16:08)
//
// Brief:
// Input:
// Output:
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <matrix.h>
#include <vector.h>
#include <qr.h>
#include <math.h>

int m = 3;
int n = 3;

double in[3][3] = {
	{  1,  -1,   4},
	{  6,   1,  -1},
	{ -4,   2,  -4},
};

int main (void){
    printf("Setting up Matrix A for QR-algorithm for square matrices...\n");
    int pre = 2;
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

    //QR-algorithm
    qrdec(Q, R, A);

    printf("Matrix R: \n");
    mat_print(R, pre); 

    printf("Matrix Q: \n");
    mat_print(A, pre);

    printf("Matrix Q' x Q: \n");
    mat_mul_T(C,A,A);
    mat_print(C, pre);
   
    printf("Matrix Q x R: \n");
    mat_mul(C, A, R);
    mat_print(C, pre);

    //Free memory
    mat_free(C);
    mat_free(A);
    mat_free(R);
    mat_free(Q);

    return 0;
}

