// Filename: test.C
// Date created: 03 May 2013
// Last Modified: 17 Jun 2013 (17:14:15)
//
// Brief: Testfile to see that vector.h functions is working
// Input: N/A
// Output: N/A
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

// C Library
#include <time.h>
#include <stdio.h>
#include "vector.h"
#include "matrix.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Lsfit library
#include "lib.h"
#define RND 1.0 

void lsfit_test(vec* c, mat* S, const vec* x, const vec* y, const vec* dy, const int nfunc, double f(int, double)){
  int n = x->size;
  int m = nfunc;
  mat* A = mat_new(n,m);
  mat* R = mat_new(m,m);
  mat* C = mat_new(m,m);
  vec* b = vec_new(n);
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
  title("Testing QR Algorithm...");
  printf("Matrix A: \n");
  mat_print(A,2);

  qrdec(A,R);
  
  printf("Matrix Q: \n");
  mat_print(A,2);
  printf("Matrix R: \n");
  mat_print(R,2);
  printf("Matrix Q^T*Q: \n");
  mat_mul_AT(C, A, A);
  mat_print(C,2);
  
  //Solve Rc = Q^T*b 
  qrback(c,A,R,b);
  
  vec* cpx = vec_new(nfunc);
  vec* cpy = vec_new(nfunc);

  // QR-algorithm on Matrix A 
  title("Testing Least Squre Fit Algorithm...");
  printf("Vector Q^T x b: \n");
  mat_mul_vec_T(cpx, A, b);
  vec_print(cpx, 2);

  printf("Vector R x c: \n");
  mat_mul_vec(cpy, R, c);
  vec_print(cpy, 2);
  
  printf("Vector c: \n");
  vec_print(c, 2);

  // Check if the answer is correct
  double sum = 0;
  vec_diff(sum, cpx, cpy);
  if (sum > 10e-16){
      printf("Least squre Algorithm failed... \n");
      exit(1);
  }
  else {
      printf("Least square Algorithm seems to be correct... \n");
  }
  // S = R^-1(R^T)^-1)
  qrinverse(R);
  mat_mul_BT(S,R,R);
  // Free memory
  mat_free(A);
  mat_free(R);
  mat_free(C);
  vec_free(b);
  vec_free(cpx);
  vec_free(cpy);
}

// Definitions
double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
double func_to_fit(double x){ return 1.0+2.0*x+3.0*x*x; }

double func(int i, double x){
   switch(i){
   case 0: return 1.0; break;
   case 1: return x;   break;
   case 2: return x*x; break;
   default: {fprintf(stderr,"funs: wron i:%d",i); return NAN;}
   }
}
int main(int argc, char** argv){
    srand(time(NULL));
    // Number of datapoints
    int n=3;
    // Allocate memory for the datapoints
    vec *x = vec_new(n);
    vec *y = vec_new(n);
    vec *dy = vec_new(n);
    // Making datapoints
    double a = -0.9;
    double b =  0.9;
    double xi,yi,dyi;
    title("# x y dy (datapoints)");
    for(int i=0; i<n; i++){
	xi = a + (b-a)*i/(n-1);
	yi = func_to_fit(xi) + RND;
        dyi = RND;
    	vec_set(x, i, xi);
        vec_set(y, i, yi);
        vec_set(dy,i, dyi);            
	printf("%4g %4g %4g \n", xi,yi, dyi);
    }
    printf("\n");

    int nfunc=3;
    vec* c = vec_new(nfunc);
    mat* S = mat_new(nfunc,nfunc);
    lsfit_test(c,S,x,y,dy,nfunc,func); 

    // Free memory
    mat_free(S);
    vec_free(c);
    vec_free(x);

    vec_free(y);
    vec_free(dy);

    return 0;
}


