// Filename: qrdec.c
// Date created: 05 May 2013
// Last Modified: 17 Jun 2013 (14:09:39)
//
// Brief: QR decomposition algorithm using Gram-Schmidt orthogonalization
// Input: Matrix A, Matrix R
// Output: modified Matrix R, 
//
// License: copyleft
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <matrix.h>
#include <vector.h>
#include <stdlib.h>

//Brief: QR decomposition 
void qrdec(mat *A, mat* R){
    double proj = 0;
    double norm = 0;
    
    // Allocates pointers of type *vec 
    //vec *coli = (vec*)malloc(sizeof(vec));
    //vec *colj = (vec*)malloc(sizeof(vec));
    vec* coli = vec_new(A->row);
    vec* colj = vec_new(A->row);

    for(int i=0; i<A->col; i++){
	mat_get_col(coli, A, i);	
	norm = vec_norm(coli);
	mat_set(R, i, i, norm);
	vec_scale(coli, 1.0/norm);
	mat_set_col(A, coli, i);
	for(int j=i+1; j<A->col; j++){
	    mat_get_col(colj, A, j);
	    proj = vec_dot(coli,colj);
	    vec_add(colj,coli,-proj);
	    mat_set_col(A, colj, j);
	    mat_set(R, i, j, proj);
	}	
    }
    // Free pointers
    vec_free(coli);
    vec_free(colj);
}


