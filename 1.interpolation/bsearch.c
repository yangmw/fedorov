// Brief: Binary search algorithm
// Author: Yang M. Wang
// Date: April 2012

#include <assert.h>
#include <stdio.h>

int bsearch(double z, double *x, double *y, int n){
	int low_idx,high_idx,mid_idx;
	low_idx = 0;	
	high_idx = n - 1;

	//printf("Inside bsearch");

	while(high_idx > low_idx + 1){
		mid_idx = (low_idx + high_idx)/2;

		//printf("z: %g \n", z);

		if(z > x[mid_idx]){
			low_idx = mid_idx;
		}
		else{
			high_idx = mid_idx;
		}
	}
	return low_idx;
}
