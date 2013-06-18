// Date created: 29 Apr 2013
// Last Modified: 17 Jun 2013 (13:25:04)
//
// Brief:
// Input:  N - number of elements for a Random NxN matrix
// Output: time in seconds it takes to solve Ax = b for 
//         my QR-algorithm and the GSL q
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

// GSL Library
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>

// C library
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

// QR library
#include <lib.h>

// Utility library
#include <matrix.h>
#include <vector.h>

// Definitions
#define RAND_MAX 10
#define FMT "%7.3f"
#define NT CblasNoTrans
#define T CblasTrans
#define pre 2

int main (int argc, char** argv){
    // Input matrix dimension from stdin
    int dim = atoi(argv[1]);
    // Allocate memory for time variables
    clock_t t1_qr,t2_qr,t1_qr_gsl,t2_qr_gsl;
    clock_t t1_lu,t2_lu,t1_lu_gsl,t2_lu_gsl;
    double time_qr, time_qr_gsl;
    double RND, sum1,sum2;
    // Allocate memory for Random matrix A and random vector b 
    double *A_val = malloc(dim*dim*sizeof(double));
    double *b_val = malloc(dim*sizeof(double));
    // Initialize the matrices
    mat* A = mat_new(dim, dim);
    mat* Q = mat_new(dim, dim);
    mat* R = mat_new(dim, dim);
    // Initialize the vectors
    vec* b = vec_new(dim);
    vec* c = vec_new(dim);
    vec* x = vec_new(dim);
    // Random seed
    srand(time(NULL));
    // Construct Random matrix A and random vector b
    for (int i=0; i<dim*dim; i++) {
	RND = (double)rand()/RAND_MAX; //Throw away first random number
	RND = (double)rand()/RAND_MAX;
    	A->val[i] = RND;
	A_val[i] = RND;
    }
    for (int i=0; i<dim; i++) {
	RND = (double)rand()/RAND_MAX;
	b->val[i] = RND;
	b_val[i];
    }
    //// Construct Random matrix A and random vector b
    //for (int i=0; i<dim; i++) {
	//RND = (double)rand()/RAND_MAX; //Throw away first random number
	//RND = (double)rand()/RAND_MAX;
	//b_val[i] = RND;
	//vec_set(b,i, b_val[i]);
	//for (int j=0; j<dim; j++) {
	    //RND = (double)rand()/RAND_MAX;
	    //A_val[i+dim*j] = RND; //Column major ordering
	    //mat_set(A,i,j,A_val[i+dim*j]);
	//}
    //}
    // Allocate memory for gsl matrix and vectors
    gsl_matrix* A_gsl = gsl_matrix_alloc(dim,dim);
    gsl_matrix* Q_gsl = gsl_matrix_alloc(dim,dim);
    gsl_vector* b_gsl = gsl_vector_alloc(dim);
    gsl_vector* c_gsl = gsl_vector_alloc(dim);
    // Fill the gsl matrix and vectors with values from A_val and b_val
    A_gsl->data = A_val;
    b_gsl->data = b_val;
    gsl_matrix_memcpy (Q_gsl, A_gsl); 
    gsl_vector *tau = gsl_vector_alloc(dim);
    gsl_vector *x_gsl = gsl_vector_alloc(dim);
    // gsl QR Algorithm for solving Ax = b
    t1_qr_gsl = clock();
    qrdec(Q, R);
    qrback(x, Q, R, b); 

    t2_qr_gsl = clock();

    gsl_blas_dgemv(NT, 1.0, A_gsl, x_gsl, 0.0, c_gsl);
    // Standard QR Algorithm for solving Ax = b
    mat_memcpy(Q,A);
    
    t1_qr = clock();
    gsl_linalg_QR_decomp(Q_gsl, tau);
    gsl_linalg_QR_solve(Q_gsl, tau, b_gsl, x_gsl);

    t2_qr = clock();
    
    mat_mul_vec(c, A, x);

    // Check if the answer is correct
    sum1 = 0;
    sum2 = 0;
    vec_diff_gsl(sum1, b_gsl, c_gsl);
    vec_diff(sum2, b, c);
    if (sum1 > 10e-16 && sum2 > 10e-16 ){
	fprintf(stderr, "QR Algorithm failed \n");
        exit(1);
    }

    time_qr =     (double)(t2_qr-t1_qr)/(CLOCKS_PER_SEC);
    time_qr_gsl = (double)(t2_qr_gsl-t1_qr_gsl)/(CLOCKS_PER_SEC);
    fprintf(stderr,"%d %0.6f %0.6f \n", dim, time_qr, time_qr_gsl);

    // Free memory 
    mat_free(A);
    mat_free(Q);
    mat_free(R);
    
    vec_free(b);
    vec_free(x);
    vec_free(c);

    gsl_vector_free(x_gsl);
    gsl_vector_free(tau);
    gsl_vector_free(b_gsl);

    gsl_matrix_free(A_gsl);
    gsl_matrix_free(Q_gsl);

    free(A_val);
    free(b_val);
    
    return 0;
}

