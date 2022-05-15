/*
 * Filename: test_deterministic_integration.c
 *
 * Summary: testing some features of the project. See "Tests" section
 * in the README file for more details.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-04
 *
 * License: see LICENSE file.
 */

#include "test_deterministic_integration.h"


double
integrate(double inf, double sup, double (*f)(double))
{
  if (inf > sup) {
    return -integrate(sup, inf, f);
  } /* end of condition */

  if (inf == sup) {
    return 0;
  } /* end of condition */

  double integral, step, start;

  integral = 0.0;
  step = 0.001;
  start = inf;
  
  while (start < sup) {
    integral += 0.5 * ((*f)(start) + (*f)(start + step)) * step;
    start += step;
  } /* end of while-loop */

  return integral;
} /* end of integrate function */


double
identity(double x)
{
  return x;
} /* end of identity function */


double
integrate_identity(double inf, double sup)
{
  return integrate(inf, sup, &identity);
} /* end of integrate_identity function */
