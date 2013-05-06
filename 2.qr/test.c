// Filename: test.C
// Date created: 03 May 2013
// Last Modified: 06 May 2013 (09:11:44)
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

int main(){
    printf("Initialize vector \n");
    int dim = 3;
    int pre = 2;

    vec v = vec_new(dim);
    vec u = vec_new(dim);
    vec w = vec_new(dim);
    mat A = mat_new(dim, dim);
    mat B = mat_new(dim, dim);
    mat C = mat_new(dim, dim);

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

    printf("Testing vector methods... \n");
    printf("u vector: \n");
    vec_print(u,"r", pre);
    printf("v vector: \n");
    vec_print(v,"r", pre);

    printf("w = u+s*v: \n");
    vec_add(u,v,1);
    vec_print(u,"r", pre);

    double value = vec_dot(u,v);
    printf("dot = u*v: %g \n", value);
    printf("norm =|u|: %g \n", vec_norm(u));

    printf("w = u.*v \n");
    w = vec_prod(u,v);
    vec_print(w,"r", pre);		

    printf("w = u./v \n");
    w = vec_div(u,v);
    vec_print(w,"r", pre);

    printf("2w = 2*w \n");
    vec_scale(w,2.0);
    vec_print(w,"r", pre);

    printf("Testing matrix methods... \n");
    printf("matrix A:\n");
    mat_print(A,pre);
    printf("matrix B: \n");
    mat_print(B,pre);

    printf("C = A+B: \n");
    C = mat_add(A,B);
    mat_print(C,pre);

    printf("C = A*B: \n");
    C = mat_mul(A,B);
    mat_print(C,pre);

    printf("C = A.*B: \n");
    C = mat_prod(A,B);
    mat_print(C,pre);

    printf("C(:,1): \n");
    w = mat_get_col(C,1);
    vec_print(w,"C",pre);

    printf("Testing vector calls...\n");
    printf("w = u+v: \n");
    for(int i=0; i<v->n; i++){
	w->val[i] = u->val[i] + v->val[i];
    }
    vec_print(w,"r",pre);

    printf("Testing matrix calls...\n");
    printf("C = A+B: \n");
    for(int i=0; i<C->row; i++){
	for(int j=0; j<C->col; j++){
	    C->val[i][j] = A->val[i][j]+B->val[i][j];  
	}
    }	
    mat_print(C,pre);

    printf("Testing matrix methods...\n");
    printf("norm(C) column: \n");
    w = mat_norm(C,"c");
    vec_print(w,"r", pre);

    printf("norm(C) row: \n");
    w = mat_norm(C,"r");
    vec_print(w,"c", pre);

    printf("Free memory \n");
    vec_free(u);
    vec_free(v);
    vec_free(w);
    mat_free(A);
    mat_free(B);
    mat_free(C);
}
