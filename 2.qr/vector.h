// Filename: vector.h
// Date created: 30 Apr 2013
// Last Modified: 06 May 2013 (09:11:50)
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
} *vec;

vec vec_new(size_t n);
void vec_free(vec v);
double vec_get(const vec v, const size_t idx);
void vec_set(vec v, const size_t idx, double val); 
void vec_print(vec v,const char *type, int precision);
vec vec_copy(const vec v);

void vec_scale(vec v,const double scale);

void vec_add(const vec u, const vec v, double s);
/*vec vec_add(const vec u, const vec v, double s);*/

vec vec_prod(const vec u, const vec v);
vec vec_div(const vec u, const vec v);
vec vec_pow(const vec v, int n);
double vec_norm(const vec v);
double vec_dot(const vec u, const vec v);

#define VECTOR_H
#endif
