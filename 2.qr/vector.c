// Filename: vector.c
// Date created: 30 Apr 2013
// Last Modified: 05 May 2013 (00:40:28)
//
// Brief: Methods for the Vector type structure
// Input: n elements 
// Output: N/A
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define VECTOR_H

typedef struct {
	size_t size, stride;
	double *value;
	bool owner;
} vec;

vec* vec_alloc(size_t size){
	//The pointer *v points to the struct of type "vec" 
	//and allocates memory
	vec *v = (vec*)malloc(sizeof(vec));
	v->size = size;
	v->stride = 1;
	v->owner = true;
	v->value = (double *)malloc(size*sizeof(double));
	return v; 
}

void vec_free(vec *v){
	assert(v->owner); 
	free(v->value); 
	free(v);
}

void vec_set(const vec *v, const size_t idx, double s){
	assert(idx < v->size && idx >= 0); 
	v->value[idx*v->stride] = s;
}

double vec_get(const vec *v, const size_t idx){
	assert(idx < v->size && idx >= 0);
	return v->value[idx*v->stride];
}

void vec_print(vec *v, const char *type, int precision){
	assert(v->size > 0 && precision < 18 && precision > 0);
	if (strcmp(type, "r") == 0){
		for(int i=0; i<v->size; i++){
			printf("  %.*f", precision, vec_get(v,i));
		}
		printf("\n");
	}
	if (strcmp(type, "c") == 0){
		for(int i=0; i<v->size; i++){
			printf("%.*f\n", precision, vec_get(v,i));
		}
	printf("# \n");
	}
}

vec* vec_add(const vec *u, const vec *v){
	assert(u->size == v->size);
	vec *w = vec_alloc(v->size);
	double y = 0;
	for(int i=0; i<v->size; i++){
		y = vec_get(u,i) + vec_get(v,i);
		vec_set(w,i,y);
	}
	return w;
}

vec* vec_sub(const vec *u, const vec *v){
	assert(u->size == v->size);
	vec *w = vec_alloc(v->size);
	double y = 0;
	for(int i=0; i<v->size; i++){
		y = vec_get(u,i) - vec_get(v,i);
		vec_set(w,i,y);
	}
	return w;
}

double vec_dot(const vec *u, const vec *v){
	assert(v->size > 0);
	double s = 0;
	for(int i=0; i<v->size; i++){
		s = s + vec_get(u,i)*vec_get(v,i);
	}
	return s;
}

vec* vec_prod(const vec *u, const vec *v){
	assert(u->size == v->size);
	vec *w = vec_alloc(v->size);
	double value = 0;
	for(int i=0; i<u->size; i++){
		value = vec_get(u,i)*vec_get(v,i);
		vec_set(w,i,value);
	}
	return w;
}

vec* vec_div(const vec*u, const vec *v){
	assert(u->size == v->size);
	vec *w = vec_alloc(v->size);
	double value = 0;
	for(int i=0; i<u->size; i++){
		value = vec_get(u,i)/vec_get(v,i);
		vec_set(w,i,value);
	}
	return w;
}

vec* vec_pow(const vec *v, int n){
	assert(v->size >0);
	vec *w = vec_alloc(v->size);
	double value = 0;
	for (int i=0; i<v->size; i++){
		value = pow(vec_get(v,i),n);
		vec_set(w,i,value);
	}
	return w;
}

double vec_norm(const vec *v){
	assert(v->size > 0);
	double norm = 0;
	norm = sqrt(vec_dot(v,v));
	return norm;
}
