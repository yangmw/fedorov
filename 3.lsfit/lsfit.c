// Filename: lsfit.c
// Date created: 13 May 2013
// Last Modified: 13 May 2013 (13:37:02)
//
// Brief:
// Input:
// Output:
//
// License: copyleft
// Original Author:
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <matrix.h>
#include <vector.h>
#include <gc.h>
#include <qrlib.h>

void lsfit(vec*c, vec* x, vec* y, vec *dy, int nfunc, double f(int k, double x)){
  int n = x->size;
  int m = nfunc;
  mat* A = mat_new(n,m);
  mat* R = mat_new(m,m);
  vec_memcpy(b,y);
 
  for(int i=0; i<n; i++){
      double xi = vec_get(x,i);
      double dyi = vec_get(dy,i);
      for(int j=0; j<m; j++){
	mat_set(A, i, k, f(k, xi)/dyi);
      }
  }
  qrdec(A,R);
  qrback(A,R,b);

  mat_free(A);
  mat_free(R);
}
