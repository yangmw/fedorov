// Filename: test.C
// Date created: 03 May 2013
// Last Modified: 17 Jun 2013 (13:07:25)
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
#include <vector.h>
#include <matrix.h>
#include <string.h>
#include <stdlib.h>

// GSL library
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <lib.h>

// Definitions
#define RND_MAX 10
#define NT CblasNoTrans
#define T CblasTrans

int main(){
    // Matrix dimension
    int dim = 3;
    // Precision
    int pre = 2;
    // Initialize the matrices
    mat* A = mat_new(dim, dim);
    mat* I = mat_new(dim, dim);
    mat* invA = mat_new(dim, dim);
    mat* C = mat_new(dim, dim);
    mat* Q = mat_new(dim, dim);
    mat* R = mat_new(dim, dim);
    // Initialize the vectors
    vec* b = vec_new(dim);
    vec* c = vec_new(dim);
    vec* x = vec_new(dim);
    // Allocate memory for matrix A and vector b
    double *A_val = malloc(dim*dim*sizeof(double));
    double *b_val = malloc(dim*sizeof(double));
    // Initialize random seed
    srand(time(NULL));
    double RND;
    double sum;
    // Fill matrix A and b with random numbers 
    for(int i=0; i<dim; i++){
	    RND = (double)rand()/RAND_MAX;	    
	    RND = (double)rand()/RAND_MAX;
	    b_val[i] = RND;
	    vec_set(b,i,b_val[i]);
	for(int j=0; j<dim; j++){
	    RND = (double)rand()/RAND_MAX;
	    A_val[i+dim*j] = RND; //Column major ordering
	    mat_set(A,i,j,A_val[i+dim*j]);
	}
    }
    
    // QR-algorithm on Matrix A 
    title("Testing QR Algorithm...");
    printf("Matrix A:\n");
    mat_print(A, pre);
    mat_memcpy(Q,A);
    qrdec(Q, R);
    printf("Matrix R: \n");
    mat_print(R, pre); 
    printf("Matrix Q: \n");
    mat_print(Q, pre);
    printf("Matrix Q^T*Q: \n");
    mat_mul_AT(C, Q, Q);
    mat_print(C, pre);
    printf("Matrix Q*Q^T: \n");
    mat_mul_BT(C, Q, Q);
    mat_print(C, pre);
    printf("Matrix Q*R: \n");
    mat_mul(C, Q, R);
    mat_print(C, pre);

    sum = mat_diff(C,A);
    if (sum > 10e-16){
	fprintf(stderr, "Qx = b Algorithm failed \n");
        exit(1);
    }

    // Solving Ax = b
    title("Testing Ax = b solver...");
    printf("Matrix A:\n");
    mat_print(A, pre);
    printf("Vector b:\n");
    vec_print(b, pre);
    qrback(x, Q, R, b); 
    printf("Vector x: \n");
    vec_print(x, pre);
    printf("Matrix A:\n");
    mat_print(A, pre);
    printf("Vector Ax:\n");
    mat_mul_vec(c, A, x);
    vec_print(c, pre);

    sum = vec_diff(c,b);
    if (sum > 10e-16){
	fprintf(stderr, "Ax = b Algorithm failed \n");
        exit(1);
    }

    // Finding the inverse of matrx A...
    title("Testing the inverse of matrix A...");
    printf("Matrix A:\n");
    mat_print(A, pre);
    mat_memcpy(invA, A);
    qrinverse(invA);
    printf("Matrix inv(A):\n");
    mat_print(invA, pre);
    printf("Matrix inv(A)*A:\n");
    mat_mul(C,invA,A);
    mat_print(C, pre);
    printf("Matrix A*inv(A):\n");
    mat_mul(C,A,invA);
    mat_print(C, pre);

    mat_set_identity(I);
    sum = mat_diff(I,C);
    if (sum > 10e-16){
	fprintf(stderr, "Ax = b Algorithm failed \n");
        exit(1);
    }

    // Testing GSL QR-algorithm...
    title("Testing Ax = b for GSL...");
    gsl_matrix* A_gsl = gsl_matrix_alloc(dim, dim);
    gsl_matrix* Q_gsl = gsl_matrix_alloc(dim, dim);
    gsl_vector* b_gsl = gsl_vector_alloc(dim);
    A_gsl->data = A_val ; // Filling A_gsl matrix with A_val
    gsl_matrix_memcpy (Q_gsl, A_gsl); 
    b_gsl->data = b_val; // Filling b_gsl matrix with b_val
    printf("Matrix A_gsl:\n");
    mat_print_gsl(A_gsl, pre);
    printf("Vector b_gsl:\n");
    vec_print_gsl(b_gsl, pre);

    gsl_vector *tau_gsl = gsl_vector_alloc(dim);
    gsl_vector *x_gsl = gsl_vector_alloc(dim);
    gsl_vector *c_gsl = gsl_vector_alloc(dim);

    gsl_linalg_QR_decomp(Q_gsl, tau_gsl);
    gsl_linalg_QR_solve(Q_gsl, tau_gsl, b_gsl, x_gsl);
    printf("Vector x_gsl:\n");
    vec_print_gsl(x_gsl, pre);
    
    // Matrix vector multiplication c = a*A*x + b*y 
    gsl_blas_dgemv(NT, 1.0, A_gsl, x_gsl, 0.0, c_gsl);
    printf("Vector A_gsl*x_gsl = b_gsl:\n");
    vec_print_gsl(c_gsl, pre);

    // Free memory
    gsl_vector_free(c_gsl);
    gsl_vector_free(b_gsl);
    gsl_vector_free(tau_gsl);
    gsl_vector_free(x_gsl);
    gsl_matrix_free(A_gsl);
    gsl_matrix_free(Q_gsl);

    mat_free(A);
    mat_free(I);
    mat_free(C);
    mat_free(Q);
    mat_free(R);
    mat_free(invA);
    vec_free(b);
    vec_free(c);
    vec_free(x);
   
    free(A_val);
    free(b_val);
    return 0;
}
