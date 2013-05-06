// Filename: vector.c
// Date created: 30 Apr 2013
// Last Modified: 06 May 2013 (10:37:29)
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
    size_t n, stride;
    double *val;
    bool owner;
} vec_t, *vec;

vec vec_new(size_t n){
    //The pointer *v points to the struct of type "vec" 
    //and allocates memory
    vec v  =  malloc(sizeof(vec_t));
    v->val =  malloc(n*sizeof(double));
    v->n = n;
    v->stride = 1;
    v->owner = true;
    return v; 
}

void vec_free(vec v){
    assert(v->owner); 
    free(v->val); 
    free(v);
}

void vec_set(const vec v, const size_t idx, double value){
    assert(idx < v->n && idx >= 0);
    v->val[idx*v->stride] = value;
}

double vec_get(const vec v, const size_t idx){
    assert(idx < v->n && idx >= 0);
    return v->val[idx*v->stride];
}

vec vec_copy(const vec a){
    vec b = vec_new(a->n);
    for(int i=0; i<a->n; i++){
	vec_set(b,i,vec_get(a,i));
    }
    return b;
}

void vec_print(vec v, const char *type, int pre){
    assert(v->n > 0 && pre < 18 && pre > 0);
    if (strcmp(type, "r") == 0){
	for(int i=0; i<v->n; i++){
	    printf("  %*.*f", pre*4, pre, vec_get(v,i));
	}
	printf("\n");
    }
    if (strcmp(type, "c") == 0){
	for(int i=0; i<v->n; i++){
	    printf("%*.*f\n", pre*4, pre, vec_get(v,i));
	}
	printf("# \n");
    }
}

void vec_scale(vec v,const double scale){
    assert(v->n > 0);
    for(int i=0; i<v->n; i++){
	vec_set(v,i, scale*vec_get(v,i));
	//v->val[i] = scale*v->val[i];
    }
}

//w = u + s*v
void vec_add(const vec u, const vec v, double s){
    assert(u->n == v->n);
    double y = 0;
    for(int i=0; i<v->n; i++){
	y = vec_get(u,i) + s*vec_get(v,i);
	vec_set(u,i,y);
    }
}

//w = u + s*v
//vec vec_add(const vec u, const vec v, double s){
    //assert(u->n == v->n);
    //vec w = vec_new(v->n);
    //double y = 0;
    //for(int i=0; i<v->n; i++){
	//y = vec_get(u,i) + s*vec_get(v,i);
	//vec_set(w,i,y);
    //}
    //return w;
//}

double vec_dot(const vec u, const vec v){
    assert(v->n > 0);
    double s = 0;
    for(int i=0; i<v->n; i++){
	s = s + vec_get(u,i)*vec_get(v,i);
    }
    return s;
}

vec vec_prod(const vec u, const vec v){
    assert(u->n == v->n);
    vec w = vec_new(v->n);
    double val = 0;
    for(int i=0; i<u->n; i++){
	val = vec_get(u,i)*vec_get(v,i);
	vec_set(w,i,val);
    }
    return w;
}

vec vec_div(const vec u, const vec v){
    assert(u->n == v->n);
    vec w = vec_new(v->n);
    double val = 0;
    for(int i=0; i<u->n; i++){
	val = vec_get(u,i)/vec_get(v,i);
	vec_set(w,i,val);
    }
    return w;
}

vec vec_pow(const vec v, int n){
    assert(v->n >0);
    vec w = vec_new(v->n);
    double val = 0;
    for (int i=0; i<v->n; i++){
	val = pow(vec_get(v,i),n);
	vec_set(w,i,val);
    }
    return w;
}

double vec_norm(const vec v){
    assert(v->n > 0);
    double norm = 0;
    norm = sqrt(vec_dot(v,v));
    return norm;
}
