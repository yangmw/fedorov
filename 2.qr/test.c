// Filename: test.c
// Date created: 03 May 2013
// Last Modified: 05 May 2013 (00:55:47)
//
// Brief: Testfile to see that vector.h functions is working
// Input: N/A
// Output: N/A
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <vector.h>
#include <string.h>

int main(){
	printf("Initialize vector \n");
	int i;
	int dim = 3;
	double value = 0;
	int pre = 2;
	vec* v = vec_alloc(dim);
	vec* u = vec_alloc(dim);
	vec* w = vec_alloc(dim);
	for(i=0; i<dim; i++){
		vec_set(v, i, (double)i);
		vec_set(u, i, (double)(2*i));
	
	
	}

	printf(" ---------%d \n", strcmp("r","r"));
	printf("Print out: \n");
	printf("u vector: \n");
	vec_print(u,"r", pre);
	printf("v vector: \n");
	vec_print(v,"r", pre);
	
	printf("w = u+v: \n");
	w = vec_add(u,v);
	vec_print(w,"r", pre);

	printf("w = u-v: \n");
	w = vec_sub(u,v);
	vec_print(w,"r", pre);

	value = vec_dot(u,v);
	printf("dot = u*v: %g \n", value);
	printf("norm =|u|: %g \n", vec_norm(u));

	printf("w = u.*v \n");
	w = vec_prod(u,v);
	vec_print(w,"c", pre);		

	printf("w = u./v \n");
	w = vec_div(u,v);
	vec_print(w,"c", pre);

	printf("Free memory \n");
	vec_free(u);
	vec_free(v);
	vec_free(w);

}
