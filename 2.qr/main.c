// Date created: 29 Apr 2013
// Last Modified: 06 May 2013 (10:37:44)
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


double in[5][3] = {
	{ 12, -51,   4},
	{  6, 167, -68},
	{ -4,  24, -41},
	{ -1, 1, 0},
	{ 2, 0, 3},
};

int main (void){
    //Setup matrix A
    printf("Setting up Matrix A for QR-algorithm...\n");
    int m = 5;
    int n = 3;
    int pre = 2;
    mat A = mat_new(m,n);
    mat R = mat_new(m,n);
    for(int i=0; i<m; i++)
	for(int j=0; j<n; j++)
	    A->val[i][j] = in[i][j]; 

    printf("Matrix A: \n");
    mat_print(A, pre);
    qrdec(A,R);

    printf("Matrix R: \n");
    mat_print(R, pre);

    printf("Matrix Q*R: \n");
    mat_print(A, pre);


    return 0;
}

