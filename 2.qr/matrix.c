// Filename: matrix.c
// Date created: 05 May 2013
// Last Modified: 06 May 2013 (10:37:40)
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
#include <string.h>

typedef struct {
	size_t row;
	size_t col;
	double **val;
	bool owner;
} mat_t, *mat;

mat mat_new(size_t m, size_t n){
  assert(m > 0 && n > 0);
  mat A = malloc(sizeof(mat_t));
  A->val = malloc(sizeof(double)*m);
  A->val[0] = calloc(sizeof(double), m*n);

  //Row Major Ordering (i.e. loop over col first) c[2][1])
  for(int i=0; i<m; i++){
    A->val[i] = A->val[0] + i*n;
  }
  A->row = m;
  A->col = n;
  A->owner = true;	
  return A;
}

void mat_free(mat A){
  assert(A->owner);
  free(A->val[0]);
  free(A->val);
  free(A);
}

double mat_get(const mat A, const size_t i, const size_t j){
  assert(i < A->row && j < A->col);
  return A->val[i][j];
}

void mat_set(const mat A, const size_t i, const size_t j, double value){
  assert(i < A->col && j < A->col);
  A->val[i][j] = value;
}

vec mat_get_col(const mat A, const size_t j){
  assert(j< A->col);
  vec v = vec_new(A->row);
  double value = 0;
  for(int i=0; i<A->row; i++){
	value = mat_get(A,i,j);
	vec_set(v,i,value);
  }
    return v;
}

//mat mat_put(int n; double a[][n], int m, int n){
	//mat A = mat_new[m][n];
	//for(int i=0; i<m; i++)
	    //for(int j=0; j<n; j++)
	    	//A->val[i][j] = a[i][j];
	//return A;
//}

void mat_print(const mat A, int pre){
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

// C(m,n) = A(m,n) + s*B(m,n)
mat mat_add(const mat A, const mat B, double s){
  assert(A->row == B->row && A->col == B->col);
  mat C = mat_new(A->row, A->col);
  double value = 0;
  for (int i=0; i<A->row; i++){
    for(int j=0; j<A->col; j++){
      value = mat_get(A,i,j) + s*mat_get(B,i,j);
      mat_set(C,i,j,value);
    }
  }
  return C;
}

// C(m,k) = A(m,n) * B(n,k) 
mat mat_mul(const mat A, const mat B){
  assert(A->col == B->row && A->col > 0 && B->col > 0);
  mat C = mat_new(A->row, B->col);
  double value = 0;
  for (int i=0; i<A->row; i++){
    for(int j=0; j<A->col; j++){
      for(int k=0; k<B->row; k++){
	value = mat_get(A,i,k)*mat_get(B,k,j);
	mat_set(C,i,j,value);
      }
    }
  }
  return C;
}

mat mat_prod(const mat A, const mat B){
  // A(m,n).*B(m,n) = C(m,n)
  assert(A->row == B->row && A->col == B->col);
  mat C = mat_new(A->row, A->col);
  double value = 0;
  for (int i=0; i<A->row; i++){
    for(int j=0; j<A->col; j++){
	value = mat_get(A,i,j)*mat_get(B,i,j);
	mat_set(C,i,j,value);
    }
  }
  return C;
}

vec mat_norm(const mat A, const char *type){
	assert(A->row > 0 && A->col > 0);
	vec v = vec_new(A->row);	
	double norm = 0;
	if (strcmp(type, "r") == 0){
	  for(int i=0; i<A->row; i++){
	    norm = 0;
	    for(int j=0; j<A->col; j++){
		norm += A->val[i][j]*A->val[i][j];
	    }
	    v->val[i] = sqrt(norm); 
	  }
	  return v;
	}
	if (strcmp(type, "c") == 0){
	  for(int j=0; j<A->col; j++){
	    norm = 0;
	    for(int i=0; i<A->row; i++){
		norm += A->val[i][j]*A->val[i][j];
	    }
	    v->val[j] = sqrt(norm); 
	  }
	  return v;
	}
	printf("Error in mat_norm \n");
	return v;
}





