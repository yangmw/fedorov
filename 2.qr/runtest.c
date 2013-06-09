// Filename: test.C
// Date created: 03 May 2013
// Last Modified: 08 Jun 2013 (17:43:07)
//
// Brief: Testfile to see that vector.h functions is working
// Input: N/A
// Output: N/A
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <time.h>
#include <stdio.h>
#include <vector.h>
#include <matrix.h>
#include <string.h>
#include <stdlib.h>

#include <lib.h>
#define RND_MAX 10

double p[3][3] = { {1, 3, -4}, {1, 1, -2}, {-1, -2, 5} };
double q[3] = {1,2,3};

int main(){
    // Matrix dimension
    int dim = 3;
    // Precision
    int pre = 2;
    // Random number
    int r = 0;
    // Initialize the matrices
    mat* A = mat_new(dim, dim);
    mat* invA = mat_new(dim, dim);
    mat* C = mat_new(dim, dim);
    mat* Q = mat_new(dim, dim);
    mat* R = mat_new(dim, dim);
    // Initialize the vectors
    vec* b = vec_new(dim);
    vec* c = vec_new(dim);
    vec* x = vec_new(dim);
    // Random number seed
    srand(time(NULL));
    // Fill matrix A with random numbers from -5 to 5
    for(int i=0; i<dim; i++){
	for(int j=0; j<dim; j++){
	    // Random number between -5 to 5
	    //r = rand()%RND_MAX - RND_MAX/2;
	    //mat_set(A, i, j, r);
	    mat_set(A, i, j, p[i][j]);
	}
    }
    // Fill vector b with random numbers from -5 to 5
    for(int i=0; i<dim; i++){
	//r = rand()%RND_MAX - RND_MAX/2;
	//vec_set(b,i,r);
	vec_set(b,i,q[i]);
    }
    // QR on Matrix A 
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

    // Finding the inverse of matrx A...
    title("Testing the inverse of matrix A...");
    printf("Matrix A:\n");
    mat_print(A, pre);
    
    mat_memcpy(invA, A);
    qr_inv(invA);
    
    printf("Matrix inv(A):\n");
    mat_print(invA, pre);

    printf("Matrix inv(A)*A:\n");
    mat_mul(C,invA,A);
    mat_print(C, pre);

    printf("Matrix A*inv(A):\n");
    mat_mul(C,A,invA);
    mat_print(C, pre);

    //Free memory
    mat_free(A);
    mat_free(Q);
    mat_free(R);
    vec_free(b);
    vec_free(c);
    vec_free(x);
}
