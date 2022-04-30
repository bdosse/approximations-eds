/*
 * Filename: numerical_approximation.c
 *
 * Summary: implements methods to give pathwise approximation of the
 * true solution of a stochastic differential equation.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-30
 *
 * License: see LICENSE file.
 */

#include "brownian_path.h"
#include "numerical_approximation.h"


static double
differentiate_at_point(double (*f)(double), double x)
{
  return (f(x + 1.0e-12) - f(x)) / 1.0e-12;
}


double *
euler_maruyama_method(double max_time, unsigned int steps, double init,	\
		      double (*determ_func)(double time, double iter) \
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
   * steps : unsigned int
   *   Number of point of the approximation. The greater, the more
   *   precise and the less it deviates from the true solution.
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
  
  double d_time = max_time / steps;
  double *path = (double)calloc(steps + 1, sizeof(double));

  double d_brownian;

  if (path != NULL) { 

    path[0] = init;
  
    for (unsigned int j = 1; j < steps; ++j) {
      d_brownian = d_time * rand_normal();
      
      path[j] = path[j - 1];
      path[j] += d_time * determ_func(j * delta_t, path[j - 1]);
      path[j] += d_brownian * stocha_func(j * delta_t, path[j - 1]);
    } /* end of for-loop */
    
  } /* end of if-condition */
  
  return path;
} /* end of euler_maruyama_method function */


double *
milstein_method(double max_time, unsigned int steps, double init, \
		double (*determ_func)(double iter), \
		double (*stocha_func)(double iter))
{
  /*
   * Compute pathwise approximation using Milstein method.
   *
   * Parameters
   * ----------
   *
   * max_time : double
   *   Maximum time allowed to perform calculation.
   *
   * steps : unsigned int
   *   Number of point of the approximation. The greater, the more
   *   precise and the less it deviates from the true solution.
   *
   * init : double
   *   Initial value of the problem to solve.
   *
   * determ_func : pointer-to-function returning double 
   *   Function taking one argument, being the stochastic process
   *   solving the problem. This function is integrated w.r.t. a
   *   deterministic integrator.
   *
   * stocha_func : pointer-to-function returning double 
   *   Function taking one argument, being the stochastic process
   *   solving the problem. This function is integrated w.r.t. a
   *   stochastic integrator.
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
  
  double d_time = max_time / steps;
  double *path = (double)calloc(steps + 1, sizeof(double));

  double d_brownian;
  double milstein_term;

  if (path != NULL) { 

    path[0] = init;
  
    for (unsigned int j = 1; j < steps; ++j) {
      d_brownian = d_time * rand_normal();
      
      milstein_term = stocha_func(path[j - 1]);
      milstein_term *= differentiate_at_point(&stocha_func, path[j - 1]);
      milstein_term *= pow(rand_normal(), 2) - d_time;
      milstein_term *= 0.5;
      
      path[j] = path[j - 1];
      path[j] += d_time * determ_func(path[j - 1]);
      path[j] += d_brownian * stocha_func(path[j - 1]);
      path[j] += milstein_term;
    } /* end of for-loop */
    
  } /* end of if-condition */
  
  return path;
} /* end of milstein_method function */
