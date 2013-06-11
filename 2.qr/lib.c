// Filename: lib.c
// Date created: 03 Jun 2013
// Last Modified: 11 Jun 2013 (12:55:15)
//
// Brief:
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <lib.h>
#include <string.h>
#include <assert.h>

void title(char *s){
    static const char padder[] = "----------------------------\n";
    printf(padder);
    printf("%s \n",s);
    printf(padder);
    printf("\n");
}

void mat_print_gsl(gsl_matrix* A_gsl, const int pre){
    assert(A_gsl->size1 > 0 && A_gsl->size2 > 0);
    assert(pre < 18 && pre > 0);
    for (int i = 0; i<A_gsl->size1; i++){
	for (int j = 0; j<A_gsl->size2; j++){
	    printf("  %*.*f", pre*4, pre, gsl_matrix_get(A_gsl, i, j));
	}
	printf("\n");
    } 
    printf("\n");
}
	   
void vec_print_gsl(gsl_vector *v, int pre){
    assert(v->size > 0 && pre < 18 && pre > 0);
    for(int i=0; i < v->size; i++){
	printf("  %*.*f", pre*4, pre, gsl_vector_get(v,i));
    }
    printf("\n");
    printf("\n");
}
