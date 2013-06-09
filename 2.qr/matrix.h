// Filename: matrix.h
// Date created: 05 May 2013
// Last Modified: 08 Jun 2013 (16:11:37)
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

//Include garbage collector
//#include <gc.h>

#ifndef MATRIX_H

typedef struct {
	size_t row;
	size_t col;
	double *val;
	bool owner;
} mat;

mat* mat_new(size_t row, size_t col);
void mat_free(mat* A);
double mat_get(const mat* A, int idx, int idy);
void mat_set(mat* A, int idx, int idy, double value);
void mat_set_id(mat* A); //Creating an identity matrix 
 
void mat_get_col(vec* c, const mat* A, const int col);
void mat_set_col(mat* A, const vec* c, const int col);

void mat_print(mat* A, int precision);
void mat_memcpy(mat* dst, const mat* src);

void mat_add(mat* A, const mat* B, double s); 		//A + B
void mat_mul(mat* C, const mat* A, const mat* B);	//A x B
void mat_mul_AT(mat* C, const mat* A, const mat* B);    //A'x B
void mat_mul_BT(mat* C, const mat* A, const mat* B);    //A x B'
void mat_mul_vec(vec* c, const mat* A, const vec* b);   //A x b 
void mat_mul_vec_T(vec* c, const mat* A, const vec* b); //A'x b

void mat_transpose(mat* A);  

double mat_det(const mat* A);

#define MATRIX_H
#endif
