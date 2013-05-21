// Filename: vector.h
// Date created: 30 Apr 2013
// Last Modified: 13 May 2013 (13:29:43)
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
	size_t size; 
	size_t stride;
	double *val;
	bool owner;
} vec;

vec* vec_new(size_t n);
void vec_free(vec* v);
double vec_get(const vec* v, const size_t idx);
void vec_zero(vec* v);
void vec_set(vec* v, const size_t idx, double val); 
void vec_print(vec* v, int precision);
void vec_memcpy(const vec* dst, const vec* src);
void vec_scale(vec* v,const double scale);
void vec_add(vec* u, const vec* v, double s);
void vec_div(vec* v, const vec* u);
double vec_norm(const vec* v);
double vec_dot(const vec* u, const vec* v);

#define VECTOR_H
#endif
