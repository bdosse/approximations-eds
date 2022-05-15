/*
 * Filename: numerical_approximation.h
 *
 * Summary: defines the numerical methods to give pathwise
 * approximation of stochastic differential equation's solutions. More
 * info can be found in the section "Approximations trajectorielles"
 * of the course notes.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-30
 *
 * License: see LICENSE file.
 */

#ifndef NUMERICAL_APPROXIMATION_H
#define NUMERICAL_APPROXIMATION_H


extern double *
euler_maruyama_method(double max_time, unsigned int steps, double init,	\
		      double (*determ_func)(double time, double iter),	\
		      double (*stocha_func)(double time, double iter));
extern double *
milstein_method(double max_time, unsigned int steps, double init, \
		double (*determ_func)(double iter), \
		double (*stocha_func)(double iter));


#endif /* NUMERICAL_APPROXIMATION_H */
