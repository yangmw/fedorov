// Filename: vector.h
// Date created: 30 Apr 2013
// Last Modified:
//
// Brief: Header file for the vector structure
// Input: number of elements
// Output:
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <studio.h>
#include <stdbool.h>

#ifndef VECTOR_H
typedef struct {
	size_t size, stride;
	double *value;
	bool owner;
} vec;

vec* vector_alloc (size_t n);
double vec_get(const vec *v, const size_t i);
void vec_set(vec *v, const size_t i, double value); 
void vec_free(vec *v);

#define VECTOR_H
#endif
