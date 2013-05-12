// Filename: matrix.c
// Date created: 05 May 2013
// Last Modified: 12 May 2013 (22:42:05)
//
// Brief: Methods for matrix type structure
// The matrix is of typedef mat with a column major structure
//
// 		offset = row + column*number_of_rows
//
// Input: (n,m) elements
// Output: N/A
//
// License:copyleft
// Original Author: Dimitir Fedorov (fedorov@chem.au.dk)
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <math.h>
#include <assert.h>
#include <vector.h>

#ifndef size_t
#include <stddef.h>
#endif

#include <stdlib.h>
#include <string.h>

// Include garbage collector
//#include <gc.h>

typedef struct {
	size_t row;
	size_t col;
	double *val;
	bool owner;
} mat;

mat* mat_new(size_t m, size_t n){
  assert(m > 0 && n > 0);
  mat* A = (mat*)malloc(sizeof(mat));
  assert(A != 0);
  A->val = (double*)malloc(m*n*sizeof(double));
  A->row = m;
  A->col = n;
  A->owner = true;	
  return A;
}

void mat_free(mat* A){
  assert(A->owner);
  free(A->val);
 free(A);
}

double mat_get(const mat* A, const size_t i, const size_t j){
  assert(i < A->row && j < A->col);
  return A->val[i+j*A->row]; //column major ordering
}

void mat_set(const mat* A, const size_t i, const size_t j, double value){
  assert(i < A->row && j < A->col);
  A->val[i+j*A->row] = value;
}

void mat_get_col(vec* c, const mat* A, const size_t i){
  assert(c->size == A->row && i < A->col);
  c->val = A->val + i*A->row;
}

void mat_set_col(mat* A, const vec* c, const size_t j){
  assert(c->size == A->row && j < A->col);
  for(int i=0; i<A->row; i++)
      mat_set(A,i,j,vec_get(c,i));
  //A->val[i*A->row] = c->val;
}

void mat_memcpy(mat* A, const mat* B){
	assert(A->row == B->row && A->col == B->col);	
	for(int i=0;i<B->row;i++) 
	    for(int j=0;j<B->col;j++)
	    mat_set(A,i,j,mat_get(B,i,j));
}
//vec* mat_get_col(const mat* A, const size_t i){
  //vec* c = (vec *)MALLOC(sizeof(vec));
  //c->size = A->row;
  //c->stride = 1;
  //c->val = A->val + i*A->row;
  //return c;
//}

void mat_print(const mat* A, int pre){
  assert(A->row > 0 && A->col > 0);
  assert(pre < 18 && pre > 0);
  for(int i=0; i<A->row; i++){
    for(int j=0; j<A->col; j++){
      printf("  %*.*f", pre*4, pre, mat_get(A,i,j));
    }
    printf("\n");
  }
  printf("# \n");
}

void mat_set_identity(mat* A){
    for(int i=0;i<A->row;i++){
	mat_set(A,i,i,1);
	for(int j=i+1;j<A->col;j++){
	    mat_set(A,i,j,0);
	    mat_set(A,j,i,0);
	}
    }
}

// A(m,n) = A(m,n) + s*B(m,n)
void mat_add(mat* A, const mat* B, double s){
  assert(A->row == B->row && A->col == B->col);
  for (int i=0; i<A->row; i++)
    for(int j=0; j<A->col; j++)
      mat_set(A,i,j,mat_get(A,i,j) + s*mat_get(B,i,j));
}

// A(m,k) = A(m,n) * B(n,k) 
void mat_mul(mat*C, const mat* A, const mat* B){
  assert(A->col == B->row);
  double sum;
  for (int i=0; i<A->row; i++){
      for(int j=0; j<B->col; j++){
	  sum = 0;
	  for(int k=0; k<B->row; k++){
	      sum +=  mat_get(A,i,k)*mat_get(B,k,j);
	  }
	mat_set(C,i,j,sum);
      }
  }
}

// A(n,m) = A(m,n)'
void mat_transpose(mat *A){
    assert(A->col > 0 && A->row > 0);
    for (int i=0; i<A->row; i++)
	for(int j=0; j<A->col; j++)
	    mat_set(A,j,i,mat_get(A,i,j));
}

// A(m,k) = A(n,m)^T x B(n,k)
void mat_mul_T(mat* C, const mat* A, const mat* B){
    assert (A->row == B->row);
    double sum;
    for (int i=0; i<A->col; i++){
	for(int j=0; j<B->col; j++){
	    sum = 0; 
	    for(int k=0; k<B->row; k++){
		sum += mat_get(A,k,i)*mat_get(B,k,j);	
	    }
	    mat_set(C,i,j,sum);
	}
    }
}

// A(m,k) = A(m,n) * B(n,k) 
void mat_mul_vec(vec* c, const mat* A, const vec* b){
  assert(b->size == A->row);
  double sum;
  for (int i=0; i<b->size; i++){
      sum = 0;
      for(int j=0; j<A->col; j++){
	  sum +=  mat_get(A,i,j)*vec_get(b,j);
      }
      vec_set(c,i,sum);
  }
}


// x(m) = A(n,m)^T x b(n)
void mat_mul_vec_T(vec*c, const mat* A, const vec* b){
    assert(A->row == b->size);
    double sum;
    for (int i=0; i<b->size; i++){
	sum = 0;
	for(int j=0; j<A->row; j++){
	    sum += mat_get(A,j,i)*vec_get(b,j);	
	}
	vec_set(c,i,sum);
	}
}

