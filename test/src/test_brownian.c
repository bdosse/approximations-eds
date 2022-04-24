/*
 * Filename: test_brownian.c
 * 
 * Summary: This file contains everything needed in order to construct
 * a Brownian motion using an Haar basis and a Faber-Schauder
 * system. Since this construction needs standard normal random
 * variable, we define a function computing a random number following
 * a standardized normal distribution thanks to the Box-Muller
 * transform.
 *
 *
 * Author: jovian <altjovian@netc.eu>
 *
 * Creation: 2022-04-03
 *
 * License: see LICENSE file.
 */

#include <math.h>
#include <stdlib.h>

#include "test_brownian.h"


double
rand_normal(void)
{
  /* 
   * Thanks to https://stackoverflow.com/a/2325531 
   * 
   * Random number generator using Box-Muller transform.
   *
   * More info in the README file.
   */

  double U, X, Y;
  double bmt;
  
  X = 0.0;
  Y = 0.0;
  U = 0.0;

  while (U > 1 || X == 0 || Y == 0) {
    X = 2.0 * (double)(rand()) / RAND_MAX - 1.0;
    Y = 2.0 * (double)(rand()) / RAND_MAX - 1.0;
    U = pow(X, 2) + pow(Y, 2);
  } /* end while-loop */

  bmt = X * sqrt(-2 * log(U) / U);

  return bmt;
} /* end of rand_normal */


double
triangle(double x)
{
  if (x >= 0 && x <= 0.5) {
    return x;
  }
  if (x > 0.5 && x <= 1) {
    return 1 - x;
  }
  else {
    return 0;
  }
} /* end of triangle */


double
schauder_basis(unsigned int scale, \
	       unsigned int shift, \
               double       x)
{
  double dilatation = pow(2.0, -0.5 * (double)scale);
  double zoom = triangle(pow(2.0, (double)scale) * x - (double)shift);

  return  dilatation * zoom;
} /* end of schauder_basis */
