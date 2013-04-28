// Date created: 28 Apr 2013
// Last Modified: 29 Apr 2013 (00:03:25)
//
// Brief:
// Input:
// Output:
//
// License:copyleft
// Original Author:
// Author:Yang Min Wang (ymwang@chem.au.dk)

#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
     
int main (void)
{
  double x, y;
  x = 5.0;
  y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);
  return 0;
}
