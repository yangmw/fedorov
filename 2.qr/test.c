// Filename: test.C
// Date created: 03 May 2013
// Last Modified: 09 May 2013 (22:01:24)
//
// Brief: Testfile to see that vector.h functions is working
// Input: N/A
// Output: N/A
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <vector.h>
#include <matrix.h>
#include <string.h>
#define colA(i) mat_get_col(A,i)

double inA[2][3] = {
	{  1, -5,  4},
	{  6,  1, -6},
};

double inB[3][4] = {
	{  1, -5,  4, 2},
	{  6,  1, -6, 3},
	{  1, -1,  2, 0},
};

int main(){
    printf("Initialize vector \n");
    int dim = 3;
    int pre = 2;

    vec *v = vec_new(dim);
    vec *u = vec_new(dim);
    vec *w = vec_new(dim);
    mat *A = mat_new(dim, dim);
    mat *B = mat_new(dim, dim);
    mat *C = mat_new(dim, dim); 
    mat *mA = mat_new(2,3);
    mat *mB = mat_new(3,4);
    mat *mC = mat_new(2,4);
	
    for(int i=0; i<2; i++){
	for(int j=0; j<3; j++){
	    mat_set(mA, i, j, inA[i][j]);
	}
    }

    for(int i=0; i<3; i++){
	for(int j=0; j<4; j++){
	    mat_set(mB, i, j, inB[i][j]);
	}
    }

    printf("Matrix multiplication with different dimension: \n");
    mat_mul(mC, mA, mB);  
    mat_print(mC, pre);

    int k=0;
    for(int i=0; i<dim; i++){
	//  printf("%d \n", i);
	vec_set(v, i, (double)i);
	vec_set(u, i, (double)(2*i));
	k++;
    }

    printf("Initialize matrix \n");
    k=0;
    for(int i=0; i<dim; i++){
	for(int j=0; j<dim; j++){
	    //  printf("%d \n", k);
	    mat_set(A, i, j, (double)k);
	    mat_set(B, i, j, (double)(2*k));
	    k++;
	}
    }

    printf("Get colum 1 from matrix A: \n");
    //mat_get_col(ck, A, 1);

    for(int i=0; i<dim; i++){
	vec_print(colA(i), pre);
    }

    //vec_print(colA(ck,1), "r", 1);

    printf("Testing vector methods... \n");
    printf("u vector: \n");
    vec_print(u, pre);
    printf("v vector: \n");
    vec_print(v, pre);

    printf("w = u+s*v: \n");
    vec_add(u,v,1);
    vec_print(u, pre);

    double value = vec_dot(u,v);
    printf("dot = u*v: %g \n", value);
    printf("norm =|u|: %g \n", vec_norm(u));

    printf("2w = 2*w \n");
    vec_scale(w,2.0);
    vec_print(w, pre);

    printf("Testing matrix methods... \n");
    printf("matrix A:\n");
    mat_print(A, pre);
    printf("matrix B: \n");
    mat_print(B, pre);
 
    printf("A = A + B: \n");
    mat_add(A,B,1.0);
    mat_print(A, pre);

    printf("C = A x B: \n");
    mat_mul(C,A,B);
    mat_print(C, pre);

    printf("Free memory \n");
    //vec_free(ck);
    vec_free(u);
    vec_free(v);
    vec_free(w);
   
    mat_free(mA);
    mat_free(mB);
    mat_free(mC);
    mat_free(A);
    mat_free(B);
    mat_free(C);
}
