// Date created: 29 Apr 2013
// Last Modified: 08 Jun 2013 (15:21:12)
//
// Brief:
// Input:
// Output:
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

// C library
#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <string.h>

// QR library
#include <lib.h>

// Utility library
#include <matrix.h>
#include <vector.h>

int main (void){
    printf("Setting up Matrix A for QR-algorithm for square matrices...\n");
    int m = 3;
    int n = 3;

    mat* A = mat_new(m,n);
    mat* Q = mat_new(m,m);
    mat* R = mat_new(m,n);
    mat* C = mat_new(m,n);
    
    title("headline");

    //Free memory
    mat_free(A);
    mat_free(Q);
    mat_free(R);
    mat_free(C);

    return 0;
}

