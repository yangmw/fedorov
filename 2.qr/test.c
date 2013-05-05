// Filename: test.c
// Date created: 03 May 2013
// Last Modified: 05 May 2013 (16:34:50)
//
// Brief: Testfile to see that vector.h functions is working
// Input: N/A
// Output: N/A
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <vector.h>
#include <matrix.h>
#include <string.h>

int main(){
  printf("Initialize vector \n");
  int dim = 3;
  int pre = 2;

  vec* v = vec_new(dim);
  vec* u = vec_new(dim);
  vec* w = vec_new(dim);
  mat* a = mat_new(dim, dim);
  mat* b = mat_new(dim, dim);
  mat* c = mat_new(dim, dim);

  for(int i=0; i<dim; i++){
    vec_set(v, i, (double)i);
    vec_set(u, i, (double)(2*i));
  }

  printf("Initialize matrix \n");
  int k=0;
  for(int i=0; i<dim; i++){
    for(int j=0; j<dim; j++){
      k++;
      mat_set(a, i, j, (double)k);
      mat_set(b, i, j, (double)(2*k));
    }
  }

  printf("Testing vector methods... \n");
  printf("u vector: \n");
  vec_print(u,"r", pre);
  printf("v vector: \n");
  vec_print(v,"r", pre);

  printf("w = u+v: \n");
  w = vec_add(u,v);
  vec_print(w,"r", pre);

  printf("w = u-v: \n");
  w = vec_sub(u,v);
  vec_print(w,"r", pre);

  double value = vec_dot(u,v);
  printf("dot = u*v: %g \n", value);
  printf("norm =|u|: %g \n", vec_norm(u));

  printf("w = u.*v \n");
  w = vec_prod(u,v);
  vec_print(w,"r", pre);		

  printf("w = u./v \n");
  w = vec_div(u,v);
  vec_print(w,"r", pre);

  printf("Testing matrix methods... \n");
  printf("matrix a:\n");
  mat_print(a,pre);
  printf("matrix b: \n");
  mat_print(b,pre);

  printf("c = a+b: \n");
  c = mat_add(a,b);
  mat_print(c,pre);

  printf("c = a-b: \n");
  c = mat_sub(a,b);
  mat_print(c, pre);

  printf("c = a*b: \n");
  c = mat_mul(a,b);
  mat_print(c,pre);

  printf("c = a.*b: \n");
  c = mat_prod(a,b);
  mat_print(c,pre);

  printf("c(:,1): \n");
  w = mat_get_col(c,1);
  vec_print(w,"c", pre);

  printf("Testing vector calls...\n");
  for(int i=0; i<v->n; i++){
	w->val[i] = u->val[i] + v->val[i];
  }
  vec_print(w,"r", pre);




  printf("Free memory \n");
  vec_free(u);
  vec_free(v);
  vec_free(w);
  mat_free(a);
  mat_free(b);
  mat_free(c);
}
