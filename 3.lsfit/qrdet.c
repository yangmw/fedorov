// Filename: qr_absdet.c
// Date created: 12 May 2013
// Last Modified: 12 May 2013 (23:43:56)
//
// Brief: 
// Input: Matrix R from a QR-decomposition
// Output: double d
//
// License: copyleft
// Author: Yang Min Wang (ymwang@chem.au.dk)

#include <matrix.h>
#include <math.h>

double qr_abs_det(const mat* R){
    double value = mat_get(R,0,0);	
    for(int i=1; i<R->row; i++)
	value = value*mat_get(R,i,i);
    
    return fabs(value);
}
