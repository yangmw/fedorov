// Filename: matrix.c
// Date created: 05 May 2013
// Last Modified: 05 May 2013 (16:36:49)
//
// Brief: Methods for matrix type structure
// The matrix is of typedef mat with a column major structure
//
// 		offset = row + column*number_of_rows
//
//
// Input: (n,m) elements
// Output: N/A
//
// License:copyleft
// Original Author: Dimitir Fedorov (fedorov@chem.au.dk)
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <assert.h>
#ifndef VECTOR_H
#include <vector.h>
#endif 
#ifndef size_t
#include <stddef.h>
#endif
#include <stdlib.h>


typedef struct {
	size_t row;
	size_t col;
	double *val;
	bool owner;
} mat;

mat* mat_new(size_t i, size_t j){
  assert(i > 0 && j > 0);
  mat *m = (mat*)malloc(sizeof(mat));
  m->val = (double*)malloc(m->row*m->col*sizeof(double));
  m->row = i;
  m->col = j;
  m->owner = true;	
  return m;
}

void mat_free(mat *m){
  assert(m->owner);
  free(m->val);
  free(m);
}

double mat_get(const mat *m, const size_t i, const size_t j){
  assert(i < m->row && j < m->col);
  return m->val[i + j*m->row];
}

vec* mat_get_col(const mat *m, const size_t j){
  assert(j < m->col && j > 0);
  vec *v = vec_new(m->row);
  double value = 0;
  for(int i=0; i<m->row; i++){
	value = mat_get(m,i,j);
	vec_set(v,i,value);
  }
    return v;
}

void mat_set(const mat *m, const size_t i, const size_t j, double value){
  assert(i < m->col && j < m->col);
  m->val[i + j*m->row] = value;
}

void mat_print(const mat *m, int pre){
  assert(m->row > 0 && m->col > 0);
  assert(pre < 18 && pre > 0);
  for(int i=0; i<m->row; i++){
    for(int j=0; j<m->col; j++){
      printf("  %*.*f", pre*4, pre, mat_get(m,i,j));
    }
    printf("\n");
  }
  printf("# \n");
}

mat* mat_add(const mat *a, const mat *b){
  // a(m,n) + b(m,n) = c(m,n)
  assert(a->row == b->row && a->col == b->col);
  mat *c = mat_new(a->row, a->col);
  double value = 0;
  for (int i=0; i<a->row; i++){
    for(int j=0; j<a->col; j++){
      value = mat_get(a,i,j) + mat_get(b,i,j);
      mat_set(c,i,j,value);
    }
  }
  return c;
}

mat* mat_sub(const mat *a, const mat *b){
  // a(m,n) + b(m,n) = c(m,n)
  assert(a->row == b->row && a->col == b->col);
  mat *c = mat_new(a->row, a->col);
  double value = 0;
  for (int i=0; i<a->row; i++){
    for(int j=0; j<a->col; j++){
      value = mat_get(a,i,j) - mat_get(b,i,j);
      mat_set(c,i,j,value);
    }
  }
  return c;
}


mat* mat_mul(const mat *a, const mat *b){
  // a(m,n) * b(n,k) = c(m,k)
  assert(a->col == b->row && a->col > 0 && b->col > 0);
  mat *c = mat_new(a->row, b->col);
  double value = 0;
  for (int i=0; i<a->row; i++){
    for(int j=0; j<a->col; j++){
      for(int k=0; k<b->row; k++){
	value = mat_get(a,i,k)*mat_get(b,k,j);
	mat_set(c,i,j,value);
      }
    }
  }
  return c;
}

mat* mat_prod(const mat *a, const mat *b){
  // a(m,n).*b(m,n) = c(m,n)
  assert(a->row == b->row && a->col == b->col);
  mat *c = mat_new(a->row, a->col);
  double value = 0;
  for (int i=0; i<a->row; i++){
    for(int j=0; j<a->col; j++){
	value = mat_get(a,i,j)*mat_get(b,i,j);
	mat_set(c,i,j,value);
    }
  }
  return c;
}
