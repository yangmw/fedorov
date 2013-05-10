// Date created: 28 Apr 2013
// Last Modified: 09 May 2013 (23:47:38)
//
// Brief: Binary search algorithm
// Input: x[n],y[n], point z 
// Output: index to the spline which point z belongs to 
//
// License:copyleft
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <assert.h>
#include <stdio.h>

int binary_search(double z, double *x, double *y, int n){
	int low_idx,high_idx,mid_idx;
	low_idx = 0;	
	high_idx = n - 1;

	while(high_idx > low_idx + 1){
		mid_idx = (low_idx + high_idx)/2;
		if(z > x[mid_idx]){
			low_idx = mid_idx;
		}
		else{
			high_idx = mid_idx;
		}
	}
	return low_idx;
}
