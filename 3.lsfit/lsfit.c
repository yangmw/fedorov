// Filename: lsfit.c
// Date created: 13 May 2013
// Last Modified: 17 Jun 2013 (16:46:13)
//
// Brief:
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include "matrix.h"
#include "vector.h"
#include "lib.h"

void lsfit(vec* c, mat* S, const vec* x, const vec* y, const vec* dy, const int nfunc, double f(int, double)){
  int n = x->size;
  int m = nfunc;
  mat* A = mat_new(n,m);
  mat* R = mat_new(m,m);
  vec* b = vec_new(n);
  vec* q = vec_new(m);
  double xi, dyi, Aik;
  vec_memcpy(b,y);
  vec_div(b,dy);
  for(int i=0; i<n; i++){
      for(int k=0; k<m; k++){
      xi  = vec_get(x,i);
      dyi = vec_get(dy,i);
      Aik = f(k, xi)/dyi;
      mat_set(A, i, k, Aik);
      }
  }
  // qr(A) = Q*R
  qrdec(A, R);
  // Solving for c: R*c = Q^T*b
  qrback(c, A, R, b);
  // Covariance matrix: S = R^-1(R^T)^-1)
  qrinverse(R);
  mat_mul_BT(S,R,R);
  // Free memory
  mat_free(A);
  mat_free(R);
  vec_free(b);
  vec_free(q);
}
