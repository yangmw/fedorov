// Filename: matrix.h
// Date created: 05 May 2013
// Last Modified: 06 May 2013 (07:49:54)
//
// Brief: Headerfile for matrix functions
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@chem.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

#ifndef size_t         
#include <stddef.h>
#endif
#include <vector.h>
#ifndef MATRIX_H

typedef struct {
	size_t row;
	size_t col;
	double **val;
	bool owner;
} mat_t, *mat;

mat mat_new(size_t row, size_t col);
void mat_free(mat A);
double mat_get(mat A, int idx, int idy);
vec mat_get_col(mat A, int col);
void mat_set(mat A, int idx, int idy, double value);

//mat mat_put(int n; double a[][n], int m, int n);

void mat_print(mat A, int precision);
mat mat_copy(const mat A);

mat mat_T(const mat A);
void mat_unit(const mat A);

vec mat_mul_vec(const mat A, vec v);
vec mat_T_mul_vec(const mat A, vec v);
vec mat_norm(mat A, const char *type);

mat mat_add(mat A, mat B);
mat mat_sub(mat A, mat B);
mat mat_mul(mat A, mat B);
mat mat_prod(mat A, mat B);
mat mat_div(mat A, mat B);

double mat_det(mat A);

#define MATRIX_H
#endif
