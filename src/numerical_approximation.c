/*
 * Filename: numerical_approximation.c
 *
 * Summary: implements method to give pathwise approximation of the
 * true solution of a stochastic differential equation.
 *
 * Implements Euler-Maruyama scheme to give strong pathwise
 * approximation of an Ito process.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-30
 *
 * License: see LICENSE file.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "brownian_path.h"
#include "numerical_approximation.h"


double *
euler_maruyama_method(double max_time, double d_time, double init, \
		      double *brownian_motion, \
		      double (*determ_func)(double time, double iter),	\
		      double (*stocha_func)(double time, double iter))
{
  /*
   * Compute pathwise approximation using Euler-Maruyama method.
   *
   * Parameters
   * ----------
   *
   * max_time : double
   *   Maximum time allowed to perform calculation.
   *
   * d_time : double 
   *   Segment discretization. It controls the number of step of the
   *   computtaion.
   *
   * init : double
   *   Initial value of the problem to solve.
   *
   * normal_random_vars : array of double
   *   Array containing random distributed variables, used in order to
   *   simulate the increment of the Brownian motion integrator.
   *
   * determ_func : pointer-to-function returning double 
   *   Function taking two argument, the first one being the time, the
   *   second one being the stochastic process solving the
   *   problem. This function is integrated w.r.t. a deterministic
   *   integrator.
   *
   * stocha_func : pointer-to-function returning double 
   *   Function taking two argument, the first one being the time, the
   *   second one being the stochastic process solving the
   *   problem. This function is integrated w.r.t. a stochastic
   *   integrator.
   *
   *
   * Returns
   * -------
   *
   * Pointer (array) of doubles. Contains 'steps + 1' values, from
   * which one can easily derive an interpolation.
   */
  if (max_time <= 0) {
    return NULL;
  }
  
  unsigned int steps = floor(max_time / d_time);
  double *path = malloc((steps + 1) * sizeof *path);

  double d_brownian;

  if (path != NULL) { 

    path[0] = init;
  
    for (unsigned int j = 1; j < steps + 1; ++j) {
      d_brownian = brownian_motion[j] - brownian_motion[j - 1];
      
      path[j] = path[j - 1];
      path[j] += d_time * determ_func(j * d_time, path[j - 1]);
      path[j] += d_brownian * stocha_func(j * d_time, path[j - 1]);
    } /* end of for-loop */
    
  } /* end of if-condition */
  
  return path;
} /* end of euler_maruyama_method function */


double *
deterministic_ito_integral(double precision, double bound,
			   double *brownian_motion,
			   double (*func)(double real))
{
  /*
   * Integration is made over the interval [0, bound], so there are
   * exactly floor(bound /precision) steps to perform. Thus,
   * brownian_motion must a an array of size at least equal to
   * floor(bound/precision).
   */

  const unsigned int steps = floor(bound / precision);
  double *integral = malloc((steps + 1) * sizeof *integral);
  
  double d_brownian;

  if (integral != NULL)
  {
    integral[0] = 0; // Integrating over [0, 0] returns 0.
    
    for (unsigned int j = 0; j < steps; ++j)
    {
      d_brownian = brownian_motion[j + 1] - brownian_motion[j];
      integral[j + 1] = integral[j];
      integral[j + 1] += func(j * precision) * d_brownian;
    } /* end of for-loop */
  } /* end of if-condition */

  return integral;
} /* end of riemannian_ito_integral function */


double *
linear_interpolation(double *data_set, unsigned int arr_size,
		     unsigned int factor)
{
  double *ids = malloc(factor * arr_size * sizeof *ids);

  if (ids != NULL && data_set != NULL)
  {
    for (unsigned int j = 0; j < arr_size; ++j)
    {
      ids[factor * j] = data_set[j];
      if (j > 0)
      {
	double increment = data_set[j] - data_set[j - 1];
	for (unsigned int k = 1; k < factor; ++k)
	{
	  ids[(j - 1) * factor + k] = data_set[j - 1];
	  ids[(j - 1) * factor + k] += (double)k / (double)factor * increment;
	} /* end of for-loop */
      } /* end of if-condition */
    } /* end of for-loop */
  } /* end of if-condition */
  
  return ids;
} /* end of interpolated_data_set function */
