// Date created: 27 Apr 2013
// Last Modified: 09 May 2013 (23:38:59)
//
// Brief: Algorithm for polynomial interpolation  
// Input: m points (x,y) 
// Output: n points(z,s)
//
// License:copyleft
// Original Author: Dimitri Fedorov (fedorov@phys.au.dk)
// Author:Yang Min Wang (ymwang@chem.au.dk)

double polinterp(double z, double *x, double *y, int n){
	double s=0;
	double p=0;
	int i,k;
	for(i=0; i<n; i++){
		p=1;
		for(k=0;k<n;k++){
			if(k!=i){
				p = p*(z-x[k])/(x[i]-x[k]);
			}
		}
		s=s+y[i]*p;
	}
	return s;
}
