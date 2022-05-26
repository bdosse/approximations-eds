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
#include <math.h>

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


double *
brownian_path(unsigned int iterations)
{
  /*
   * The definition of a brownian motion gives a naive way to compute
   * a brownian path. We need numbers following a gaussian.
   */
  
  double step = 0;
  double *path = malloc(iterations * sizeof *path);

  /*
   * Let h > 0; since B(t + h) - B(t) \sim N(0, h), it follows that
   * B(t + h) = B(t) + \delta where \delta \sim N(0, h). 
   *
   * Implementation : \delta = h * rand_normal
   */
  
  if (path != NULL) {

    path[0] = 0; 
    
    for (unsigned int i = 1; i < iterations; ++i) {
      step = sqrt(1.0 / iterations) * rand_normal();
      path[i] = path[i - 1] + step; 
    } /* end of for-loop */

  } /* end of if-condition */

  return path;
} /* end of intuitive_brownian_path function */
