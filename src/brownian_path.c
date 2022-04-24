/*
 * Filename: brownian_path.c
 * 
 * Summary: This file contains everything needed in order to construct
 * a brownian path using an Haar basis and a Faber-Schauder
 * system. Since this construction needs standard normal random
 * variable, we define a function computing a random number following
 * a standardized normal distribution thanks to the Box-Muller
 * transform.
 *
 * Author: bdj <bdosse@student.uliege.be>
 *
 * Creation: 2022-04-03
 *
 * License: see LICENSE file.
 */

#include <stdlib.h>

#include "brownian_path.h"


double
rand_normal(void)
{
  /* 
   * Thanks to https://stackoverflow.com/a/2325531 
   * 
   * Random number generator using Box-Muller transform.
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
} /* end of rand_normal function */


static double
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
} /* end of triangle function */


static double
schauder_basis(unsigned int scale, \
	       unsigned int shift, \
               double       x)
{
  double dilatation = pow(2.0, -0.5 * scale);
  double zoom = triangle(pow(2.0, scale) * x - shift);

  return  dilatation * zoom;
} /* end of schauder_basis function */


double
schauder_brownian_path(unsigned int step, double time)
{
  /*
   * Using the Schauder basis (also known as Faber-Schauder system),
   * we can compute a Brownian path on the segment [0,1].
   *
   * The step plays the scale's role, but one must keep in mind that
   * there is scale * pow(2, scale) call to the schauder_basis
   * function.
   *
   * This implementation is extremely inefficient, I keep it for
   * educational purpose only.
   */
  
  double brownian = 0;
  
  for (unsigned int j = 0; j < step + 1; ++j) {

    for (unsigned int k = 0; k < pow(2, j); ++k) {
      brownian += rand_normal() * schauder_basis(j, k, time);
    } /* end of inner for-loop */
    
  } /* end of outer for-loop */

  brownian += rand_normal() * time;

  return brownian;
} /* end of schauder_brownian_path function */


double
donsker_brownian_path(unsigned int step, double time)
{
  /*
   * Donsker theorem allows easy creation of Brownian path. It's as
   * easy as using the CLT.
   *
   * This implementation uses Box-Müller transform in order to get
   * pseudo-random numbers distributed according to a standard
   * gaussian. One can easily use the default C PRNG.
   */
  
  double LIMIT_D = step * time;
  double LIMIT_FLOOR = floor(LIMIT_D);
  
  double brownian_path = 0;

  for (unsigned int j = 0; j < LIMIT_FLOOR; ++j) {
    brownian_path += rand_normal();
  } /* end of for-loop */

  brownian_path += (LIMIT_D - LIMIT_FLOOR) * rand_normal();
  brownian_path /= sqrt(step);

  return brownian_path;
} /* end of downsker_brownian_path function */


double *
naive_brownian_path(unsigned int iterations)
{
  /*
   * The definition of a brownian motion gives a naive way to compute
   * a brownian path. We need numbers following a gaussian.
   */
  
  double step = 0;
  double *brownian_path = (double *)calloc(iterations, sizeof(double));

  /*
   * Let h > 0; since B(t + h) - B(t) \sim N(0, h), it follows that
   * B(t + h) = B(t) + \delta where \delta \sim N(0, h). 
   *
   * Implementation : \delta = h * rand_normal
   */
  
  if (brownian_path != NULL) {

    brownian_path[0] = 0; 
    
    for (unsigned int i = 1; i < iterations; ++i) {
      step = sqrt(1.0 / iterations) * rand_normal();
      brownian_path[i] = brownian_path[i - 1] + step; 
    } /* end of for-loop */

  } /* end of if-condition */

  return brownian_path;
} /* end of intuitive_brownian_path function */
