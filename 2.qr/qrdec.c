// Filename: qrdec.c
// Date created: 05 May 2013
// Last Modified: 06 May 2013 (09:12:42)
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
#define colA(i) mat_get_col(A, i)

//QR decomposition
void qrdec(mat A, mat R){
    //Finding the norm of the columns of A = {a_1|a_2|a_3...}
    double norm = 0;	
    double proj = 0;
    for(int i=0; i<A->col; i++){
    	norm = vec_norm(colA(i));
	printf("norm %g \n",norm);
	R->val[i][i] = norm;
	vec_scale(colA(i), 1.0/norm);
	for(int j=i+1; j<A->col; j++){
	    vec_print(colA(i),"r",2);
	    vec_print(colA(j),"r",2);
	    proj = vec_dot(colA(i),colA(j));
	    printf("proj %g \n", proj);
	    //A is replaced with Q-matrix
	    //printf("%d %d \n", i,j);
	    vec_add(colA(j), colA(i), -proj);	
	    R->val[i][j] = proj;
	}
    }
}
