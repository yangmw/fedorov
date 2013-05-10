// Filename: matrix.h
// Date created: 05 May 2013
// Last Modified: 09 May 2013 (23:54:10)
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
	double *val;
	bool owner;
} mat;

mat* mat_new(size_t row, size_t col);
void mat_free(mat* A);
double mat_get(mat* A, int idx, int idy);
void mat_set(mat* A, int idx, int idy, double value);
void mat_set_idenity(mat* A);

vec* mat_get_col(const mat* A, const int col);

void mat_print(mat* A, int precision);
void mat_memcpy(mat* dst, const mat* src);

void mat_add(mat* A, const mat* B, double s);
void mat_mul(mat* C, const mat* A, const mat* B);
void mat_mul_T(mat* C, const mat* A, const mat* B);
void mat_transpose(mat* A);

double mat_det(const mat* A);

#define MATRIX_H
#endif
