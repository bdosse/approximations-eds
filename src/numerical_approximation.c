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
#include <stdlib.h>

#include "brownian_path.h"
#include "numerical_approximation.h"


double *
euler_maruyama_method(double max_time, double d_time, double init,	\
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
      d_brownian = d_time * rand_normal();
      
      path[j] = path[j - 1];
      path[j] += d_time * determ_func(j * d_time, path[j - 1]);
      path[j] += d_brownian * stocha_func(j * d_time, path[j - 1]);
    } /* end of for-loop */
    
  } /* end of if-condition */
  
  return path;
} /* end of euler_maruyama_method function */
