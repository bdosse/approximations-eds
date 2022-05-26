/*
 * Filename: config.h
 *
 * Summary: configuration file for solving numerically some SDE.
 *
 * This configuration file may be changed before compilation in order
 * to solve different SDE. As of now (2022, May), the only algorithm
 * available is the Euler-Maruyama scheme.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-05-24
 *
 * License: see LICENSE file.
 */
#ifndef _CONFIG_H
#define _CONFIG_H

#include "data_manipulation.h"

typedef enum {IO_ERROR=-32, CANNOT_ALLOCATE_SDS, CANNOT_CREATE_DIRECTORY,
  INVALID_STEP_PRECISION, INVALID_TIME_BOUND, INFINITY_OCCURENCE, NAN_OCCURENCE,
  SUCCESS=0}
  state;

void dummy(double first_arg, double second_arg)
{
  /* Silence warning about unused arguments. */
  (void) first_arg;
  (void) second_arg;
  return;
}

/*
 * !!! EDIT ANYTHING ABOVE THIS LINE AT YOUR OWN RISK !!!
 */


/*
 * One may use another math functions provider. However, the function
 * double pow(double, double) needs to be defined for step precision
 * (one may also change the definition of step precision).
 */
#include <math.h>


/*
 * Silent mode.
 *
 * When running this utility in a script, it may be convenient to
 * silent every warning. In this case, uncomment the following macro.
 */
/* #define SILENT */


/*
 * CSV means "Comma-Separated Values"; however, it is common to store
 * data which are not separated by comma, but by semicolon, or single
 * (or double) space(s). 
 *
 * Available options are: COMMA, SEMICOLON, SINGLE_SPACE,
 * DOUBLE_SPACE.
 *
 * Default value: COMMA
 */
csv_format FORMAT = COMMA;


/*
 * Path of output data.
 * Be careful when editing this! Better is to keep it as it is!
 *
 * Default value: "./data/"
 */
#define FILEPATH "./data"


/*
 * An (Ito) SDE is composed with two terms: a deterministic one, and a
 * stochastic one. The deterministic term is the one integrated with
 * respect to the Lebesgue integral, whereas the stochastic term is
 * integrated with respect to the Ito integral.
 *
 * An Ito SDE is associated with an initial condition. This initial
 * condition may be a random variable or a scalar.
 */

/*
 * Deterministic term of the SDE. See above for more details.
 *
 * Default: dummy function returning 1.0
 */
double
deterministic_term(double time, double pos)
{
  dummy(time, pos);
  return pos;
} /* end of deterministic_term function */


/*
 * Stochastic term of the SDE. See above for more details.
 *
 * Default: dummy function returning 0.0
 */
double
stochastic_term(double time, double pos)
{
  dummy(time, pos);
  return pos;
} /* end of stochastic_term function */


/*
 * Initial condition.
 *
 * Since it may be a random variable, it is implemented as a function.
 *
 * Default: dummy function returning 1.0
 */
double
initial_condition(void)
{
  return 1.0;
} /* end of initial_condition function */


/*
 * Set the time bound.
 *
 * The solution is computed over a closed interval [0, T].
 *
 * Default value: 1.0
 */
#define TIME_BOUND 1.0


/*
 * Step precision.
 *
 * As every iterative computation, one needs to set a step
 * precision. Be aware of error propagation. 
 *
 * Default value: pow(2, -7).
 */
#define STEP_PRECISION pow(2, -7)


/*
 * The pseudo-random number generator needs to be initialized. 
 *
 * If USE_TIME is defined, the pseudo-random number generator will
 * use a seed based on launch time.
 *
 * This option takes precedence over PRNG_SEED.
 *
 * Comment the macro to use PRNG_SEED instead.
 */
/* #define USE_TIME */


/*
 * Pseduo-random number generator seed.
 *
 * In order to reproduce some behavior, one may want to set the
 * pseudo-random number generator seed.
 *
 * Default value: 37
 */
#define PRNG_SEED 37

/*
 * Number of iteration.
 *
 * If defined, will generate ITER trajectories. Trajectories will be
 * stored in different files.
 *
 * Commenting the macro has the same effect as setting it to 1.
 *
 * Default value: 1
 */
#define ITER 1


/*
 * Printed precision
 *
 * Change the precision of floating point number printed in files.
 *
 * Default value: 10
 */
#define FLOAT_PREC 10


#endif /* _CONFIG_H */
