// Filename: vector.c
// Date created: 30 Apr 2013
// Last Modified: 30 Apr 2013 (21:51:06)
//
// Brief: Methods for the Vector type structure
// Input: n elements 
// Output: N/A
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#define VECTOR_H

typdef struct {
	size_t size, stride;
	double *value;
	bool owner;
} vec;

vec* vec_alloc(size_t n){
	//Pointer v points to the struct of type "vec" 
	//and allocates memory
	vec *v = (vec *)malloc(sizeof(vec));
	v->size = n;
	v->stride = 1;
	v->owner = TRUE;
	v->value = (double *)malloc(n*sizeof(double));
	return v; 
}

void vec_free(vec *v){
	assert(v->owner); 
	free(v->value); 
	free(v);
}
