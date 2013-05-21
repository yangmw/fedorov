// Filename: qrdec.c
// Date created: 05 May 2013
// Last Modified: 13 May 2013 (13:10:05)
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

//Brief: QR decomposition 
void qrdec(mat* A, mat *R){
    //Finding the norm of the columns of A = {a_1|a_2|a_3|...}
    //double norm = 0;	
    double proj = 0;
    double norm = 0;
    vec *coli = vec_new(A->row);
    vec *colj = vec_new(A->row);
    for(int i=0; i<A->col; i++){
	mat_get_col(coli,A,i);	
	norm = vec_norm(coli);
	mat_set(R,i,i, norm);
	vec_scale(coli, 1.0/norm);
	mat_set_col(A,coli,i);
	for(int j=i+1; j<A->col; j++){
	    mat_get_col(colj,A,j);
	    proj = vec_dot(coli,colj);
	    //A is replaced with Q-matrix
	    vec_add(colj,coli,-proj);	
	    mat_set(R,i,j,proj);
	}	
    }
   //vec_free(coli);
   //vec_free(colj);
}


