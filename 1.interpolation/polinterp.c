//Brief: Algorithm for polynomial interpolation 
//Input: point z the interpolant, vector of points x and y, number of points n
//Output: value of the interoplant at point z
//
//Original author: Dimitri Fedorov (fedorov@phys.au.dk)
//Author: Yang Min Wang (ymwang@chem.au.dk)
//Date: April 2013

double polinterp(double z, double *x, double *y, int n){
	double s=0;
	double p=0;
	int i,k;
	for(i=0; i<n; i++){
		p=1;
		for(k=0;k<n;k++){
			if(k!=i){
				p = p*(z-x)/(x[i]-x[k]);
			}
		}

	}

}
