/*
 * Filename: compute_approximation.c
 *
 * Summary: compute an approximation of an Ito process.
 *
 * The approximation is calculated thanks to the Euler-Maruyama
 * process. Configuration is done through the config.h file, following
 * an idea from the suckless.org community.
 *
 * To configure this program, take a look at the config.h file.
 *
 * !!! EDIT THIS FILE AT YOUR OWN RISK !!!
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-03
 *
 * License: see LICENSE file.
 */

#include <sys/stat.h>

#include "config.h"

#ifdef USE_TIME
#include <time.h>
#else
#ifndef PRNG_SEED
#define PRNG_SEED 37
#endif
#endif

#ifndef FILEPATH
#define FILEPATH "./data"
#endif

#ifndef FLOAT_PREC
#define FLOAT_PREC 10
#endif

#ifndef ITER
#define ITER 1
#endif

#ifndef STEP_PRECISION
#define STEP_PRECISION pow(2, -7)
#endif

#ifndef TIME_BOUND
#define TIME_BOUND 1.0
#endif

#ifdef COMPARE
#define STEPS floor(TIME_BOUND / BROWNIAN_PRECISION) + 1
#define FACTOR floor(STEP_PRECISION / BROWNIAN_PRECISION)
#ifndef BROWNIAN_PRECISION
#define BROWNIAN_PRECISION STEP_PRECISION
#endif
#else
#define STEPS floor(TIME_BOUND / STEP_PRECISION) + 1
#endif


int
main(void)
{
  #ifdef USE_TIME
  srand((unsigned int)time(NULL));
  #else
  srand((unsigned int)PRNG_SEED);
  #endif

  /* Type safety */
  const char *filepath = FILEPATH;
  const unsigned int float_prec = FLOAT_PREC;
  const unsigned int iter = ITER;
  const double step_precision = STEP_PRECISION;
  const unsigned int steps = STEPS;
  const double time_bound = TIME_BOUND;
  #ifdef COMPARE
  const double brownian_precision = BROWNIAN_PRECISION;
  const unsigned int factor = FACTOR;
  const unsigned int truncation = floor(time_bound / step_precision) + 1;
  #else
  #endif
  
  
  /* Mandatory verifications */
  if (step_precision <= 0)
  {
    #ifndef SILENT
    printf("Fatal:  step_precision cannot be less than zero.\n");
    #endif
    return INVALID_STEP_PRECISION;
  }

  #ifdef COMPARE
  if (brownian_precision > step_precision)
  {
    #ifndef SILENT
    printf("Fatal:  brownian_precision cannot be greater than step_precision.\n");
    #endif
    return INVALID_BROWNIAN_PRECISION;
  }
  #endif

  if (time_bound < 0)
  {
    #ifndef SILENT
    printf("Fatal:  time_bound must be positive.\n");
    #endif
    return INVALID_TIME_BOUND;
  }

  if (iter < 1)
  {
    #ifndef SILENT
    printf("Fatal:  iter must be an integer and cannot be less than 1.\n");
    #endif
    return INVALID_ITERATION_NUMBER;
  }

  /* It sucks if there's no folder where to store the data. */
  struct stat st = {0};
  if (stat(filepath, &st) == -1)
  {
    #ifndef SILENT
    printf("Warn:    Directory %s does not exist.\n", filepath);
    printf("         Creating it...\n");
    #endif
    if(mkdir(filepath, 0700) == -1)
    {
      #ifndef SILENT
      printf("Fatal:   Cannot create directory %s.\n", filepath);
      printf("         Check you have the permission to do so.\n");
      #endif
      return CANNOT_CREATE_DIRECTORY;
    }
  }

  /* Polite warning before computing */
  #ifndef SILENT
  printf("Destination path:       %s\n", filepath);
  printf("Number of simulation:   %d\n", iter);

  #ifdef USE_TIME
  printf("Seed:                   Time based\n");
  #else
  printf("Seed:                   %d\n", PRNG_SEED);
  #endif
  
  printf("Precision:              %f\n", step_precision);
  if (step_precision <= 0.0000001)
  {
    printf("Warn:   step_precision is very low.\n");
    printf("        It may result in unexpected behaviour.\n");
    /* Read: "I'm too lazy to compute error propagation." */
  }
  
  printf("Interval of simulation: [0, %.4f]\n", time_bound);
  #endif
  
  /* We can proceed to try to compute a solution. */
  sds *storage = init_sds();
  sds_store_precision(storage, float_prec);
  state status;

  /*
   * If precision of the Brownian motion is set to 2^{-m} and
   * precision of the Euler approximation is set to 2^{-n} with m >=
   * n, then we need to:
   *
   *   0. Know whether we are comparing or not;
   *   1. Interpolate data -> linear_interpolation function;
   *   2. Store interpolated date along simulation of the reference
   *      process.
   *
   * If we are comparing, we may decide to generate a more precise
   * Brownian motion.
   */  
  
  if (storage == NULL)
  {
    #ifndef SILENT
    printf("Fatal:   Not enough space (heap) to allocate for storage utility.");
    #endif
    return CANNOT_ALLOCATE_SDS;
  }
  
  for (unsigned int i = 0; i < iter; ++i)
  {
    double *brownian_motion;
    char filename[128];
    FILE *output;
    double *path;
    #ifdef COMPARE    
    double *interpolation;
    double *reference;
    double time_pos[3];
    double truncated_brownian_motion[truncation];
    #else
    double time_pos[2];
    #endif
  
    snprintf(filename, 128, "%s/data_%d.csv", filepath, i + 1);
    
    output = fopen(filename, "w");
    brownian_motion = brownian_path(steps);
    
    #ifdef COMPARE
    for (unsigned int j = 0; j < truncation; ++j)
    {
      truncated_brownian_motion[j] = brownian_motion[factor * j];
    }
    path = euler_maruyama_method(time_bound, step_precision,
				 initial_condition(), truncated_brownian_motion,
				 &deterministic_term, &stochastic_term);
    interpolation = linear_interpolation(path, truncation, factor);
    reference = reference_process(brownian_motion);
    #else
    path = euler_maruyama_method(time_bound, step_precision,
				 initial_condition(), brownian_motion,
				 &deterministic_term, &stochastic_term);
    #endif
    
    /* Now printing in file */
    if (output != NULL)
    {
      for (unsigned int j = 0; j < steps; ++j)
      {
	#ifdef COMPARE
	time_pos[0] = j * brownian_precision;
	time_pos[1] = interpolation[j];
	time_pos[2] = reference[j];
	sds_store_array_double(storage, time_pos, 3);
	#else
	time_pos[0] = j * step_precision;
	time_pos[1] = path[j];
	sds_store_array_double(storage, time_pos, 2);
	#endif
	
	print_sds_in_csv(output, FORMAT, storage);
      }
    
      #ifndef SILENT
      printf("Success: Computation %d/%d terminated.\n", i + 1, iter);
      printf("         Results stored in '%s'\n", filename);
      #endif
      status = SUCCESS;
    }
    else
    {
      #ifndef SILENT
      printf("Fatal:   Unable to print data in CSV file (I/O error).\n");
      #endif
      status = IO_ERROR;
    }

    fclose(output);
    #ifdef COMPARE
    free(interpolation);
    free(reference);
    #endif
    free(path);
    free(brownian_motion);
  }
  
  free(storage);  
  return status;
} /* end of main */
