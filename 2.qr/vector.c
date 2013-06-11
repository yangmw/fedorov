// Filename: vector.c
// Date created: 30 Apr 2013
// Last Modified: 11 Jun 2013 (11:39:16)
//
// Brief: Methods for the Vector type structure
// Input: n elements 
// Output: N/A
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

typedef struct {
    size_t size;
    size_t stride;
    double *val;
    bool owner;
} vec;

vec* vec_new(size_t n){
    vec* v  = (vec*)malloc(sizeof(vec));
    v->size = n;
    v->stride = 1;
    v->val =  (double*)malloc(n*sizeof(double));
    v->owner = true;
    return v; 
}

void vec_free(vec* v){
    assert(v->owner); 
    free(v->val);
    free(v);
}

void vec_set(const vec* v, const size_t idx, double value){
    assert(idx < v->size && idx >= 0);
    v->val[idx*v->stride] = value;
}

double vec_get(const vec* v, const size_t idx){
    assert(idx < v->size && idx >= 0);
    return v->val[idx*v->stride];
}

void vec_zero(vec* v){
    for(int i=0; i<v->size; i++)
	vec_set(v,i,0);
}

void vec_memcpy(const vec* dst, const vec* src){
    assert(dst->size == src->size);
    for(int i=0; i<src->size; i++)
	vec_set(dst,i,vec_get(src,i));
}

void vec_print(vec* v, int pre){
    assert(v->size > 0 && pre < 18 && pre > 0);
	for(int i=0; i<v->size; i++){
	    printf("  %*.*f", pre*4, pre, vec_get(v,i));
	}
	printf("\n");
	printf("\n");
}

//v = v*s
void vec_scale(vec *v, const double scale){
    for(int i=0; i<v->size; i++)
	vec_set(v,i, scale*vec_get(v,i));
}

//v = v + s*u
void vec_add(vec* v, const vec* u, double s){
    assert(u->size == v->size);
    double y = 0;

    for(int i=0; i<v->size; i++){
	y = vec_get(v,i) + s*vec_get(u,i);
	vec_set(v,i,y);
    }
}

//s = v dot u
double vec_dot(const vec* u, const vec* v){
    assert(v->size == u->size);
    double s = 0;
    for(int i=0; i<v->size; i++){
	s = s + vec_get(u,i)*vec_get(v,i);
    }
    return s;
}

//||v||
double vec_norm(const vec* v){
    assert(v->size > 0);
    double norm = 0;
    norm = sqrt(vec_dot(v,v));
    return norm;
}

void vec_comp(double sum, const vec* v, const vec* w){
    assert(v->size == w->size);
    for(int i=0; i<v->size; i++)
	sum += vec_get(v,i)-vec_get(w,i);
}

#endif /* VECTOR_H */
