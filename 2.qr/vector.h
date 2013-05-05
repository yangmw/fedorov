// Filename: vector.h
// Date created: 30 Apr 2013
// Last Modified: 05 May 2013 (16:29:22)
//
// Brief: Header file for the vector structure
// Input: number of elements
// Output:
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <stdbool.h>

#ifndef VECTOR_H
typedef struct {
	size_t n, stride;
	double *val;
	bool owner;
} vec;

vec* vec_new(size_t n);
void vec_free(vec *v);
double vec_get(const vec *v, const size_t idx);
void vec_set(vec *v, const size_t idx, double val); 
void vec_print(vec *v,const char *type, int precision);

vec* vec_add(const vec *u, const vec *v);
vec* vec_sub(const vec *u, const vec *v);
vec* vec_prod(const vec *u, const vec *v);
vec* vec_div(const vec *u, const vec *v);
vec* vec_pow(const vec *v, int n);
double vec_norm(const vec *v);
double vec_dot(const vec *u, const vec *v);

#define VECTOR_H
#endif
