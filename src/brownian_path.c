/*
 * Filename: brownian_path.c
 * 
 * Summary: This file contains everything needed in order to construct
 * a brownian path. Since this construction needs standard normal
 * random variable, we define a function computing a random number
 * following a standardized normal distribution thanks to the
 * Box-Muller transform.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation: 2022-04-03
 *
 * License: see LICENSE file.
 */

#include <stdlib.h>
#include <math.h>

#include "brownian_path.h"
#include "config.h"

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
brownian_path(double max_time, double brownian_prec)
{
  /*
   * The definition of a brownian motion gives a naive way to compute
   * a brownian path. We need numbers following a gaussian
   * distribution.
   */
  
  double step = 0;
  double length = max_time / brownian_prec;
  double *path = malloc(length * sizeof *path);

  /*
   * Let h > 0, and denote the standard Brownian motion by B; since
   * B(t + h) - B(t) \sim N(0, h), it follows that B(t + h) = B(t) +
   * \delta where \delta \sim N(0, h).
   *
   * Implementation : \delta = \sqrt(h) * rand_normal
   */
  
  if (path != NULL) {

    path[0] = 0; 
    
    for (unsigned int i = 1; i < length; ++i) {
      step = sqrt(brownian_prec) * rand_normal();
      path[i] = path[i - 1] + step; 
    } /* end of for-loop */

  } /* end of if-condition */

  return path;
  
} /* end of brownian_path function */


