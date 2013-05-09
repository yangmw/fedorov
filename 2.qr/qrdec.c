// Filename: qrdec.c
// Date created: 05 May 2013
// Last Modified: 09 May 2013 (22:48:55)
//
// Brief: QR decomposition algorithm using Gram-Schmidt orthogonalization
// Input: Matrix A, Matrix R
// Output: modified Matrix R, 
//
// License: copyleft
// Original Author: Dimitri Fedorov (fedorov@chem.au.dk)
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <matrix.h>
#define colA(i) mat_get_col(A,i)

//QR decomposition
void qrdec(mat* Q, mat *R, mat* A){
    //Finding the norm of the columns of A = {a_1|a_2|a_3...}
    //double norm = 0;	
    double proj = 0;
    double norm = 0;
    for(int i=0; i<A->col; i++){
	norm = vec_norm(colA(i));
	mat_set(R,i,i, norm);
	vec_scale(colA(i), 1.0/norm);
	for(int j=i+1; j<A->col; j++){
	    proj = vec_dot(colA(i),colA(j));
	    //A is replaced with Q-matrix
	    vec_add(colA(j), colA(i), -proj);	
	    mat_set(R,i,j, proj);
	}
    }
    // Free matrix
}
