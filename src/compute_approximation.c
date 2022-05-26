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

#include <stdlib.h>
#include <sys/stat.h>

#include "config.h"
#include "data_manipulation.h"
#include "numerical_approximation.h"

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


int
main(void)
{
  #ifdef USE_TIME
  srand((unsigned int)time(NULL));
  #else
  srand((unsigned int)PRNG_SEED);
  #endif

  /* Mandatory verifications */
  if (STEP_PRECISION <= 0)
  {
    #ifndef SILENT
    printf("Fatal:  STEP_PRECISION cannot be less than zero.\n");
    #endif
    return INVALID_STEP_PRECISION;
  }

  if (TIME_BOUND < 0)
  {
    #ifndef SILENT
    printf("Fatal:  TIME_BOUND must be positive.\n");
    #endif
    return INVALID_TIME_BOUND;
  }

  #ifndef SILENT
  if (STEP_PRECISION <= 0.0000001)
  {
    printf("Warn:   STEP_PRECISION is very low.\n");
    printf("        It may result in unexpected behaviour.\n");
    /* Read: "I'm too lazy to compute error propagation." */
  }
  #endif

  /* Polite warning before computing */
  #ifndef SILENT
  printf("Destination path:       %s\n", FILEPATH);
  printf("Number of simulation:   %d\n", ITER);
  printf("Interval of simulation: [0, %.4f]\n", TIME_BOUND);
  #endif

  
  /* We can proceed to try to compute a solution. */
  sds *storage = init_sds();
  sds_store_precision(storage, FLOAT_PREC);

  double *path;
  double time_pos[2];
  char filename[128];
  state status;

  if (storage == NULL)
  {
    #ifndef SILENT
    printf("Fatal:   Not enough space to allocate for storage utility.");
    #endif
    return CANNOT_ALLOCATE_SDS;
  }
  
  /* It sucks if there's no folder where to store the data. */
  struct stat st = {0};
  if (stat(FILEPATH, &st) == -1)
  {
    #ifndef SILENT
    printf("Warn:    Directory %s does not exist.\n", FILEPATH);
    printf("         Creating it...\n");
    #endif
    if(mkdir(FILEPATH, 0700) == -1)
    {
      #ifndef SILENT
      printf("Fatal:   Cannot create directory %s.\n", FILEPATH);
      printf("         Check you have the permission to do so.\n");
      #endif
      return CANNOT_CREATE_DIRECTORY;
    }
  }
  

  /* What if ITER <= 0? */
  for (unsigned int i = 0; i < ITER; ++i)
  {
    snprintf(filename, 128, "%s/data_%0d.csv", FILEPATH, i + 1);

    const unsigned int size = floor(TIME_BOUND / STEP_PRECISION);
    FILE *output = fopen(filename, "w");
    
  
    path = euler_maruyama_method(TIME_BOUND,
				 STEP_PRECISION,
				 initial_condition(),
				 deterministic_term,
				 stochastic_term);
  
    if (output != NULL)
    {
      for (unsigned int j = 0; j < size; ++j)
      {
	time_pos[0] = j * STEP_PRECISION;
	time_pos[1] = path[j];
	sds_store_array_double(storage, time_pos, 2);
	print_sds_in_csv(output, FORMAT, storage);

	if (fabs(path[j]) == INFINITY)
	{
	  #ifndef SILENT
	  printf("Fatal:   INFINITY value occured.\n");
	  printf("         No further calculation allowed.\n");
	  #endif
	  status = INFINITY_OCCURENCE;
	}

	if (isnan(path[j]))
	{
	  #ifndef SILENT
	  printf("Fatal:   NAN value occured.\n");
	  printf("         No further calculation allowed.\n");
	  #endif
	  status = NAN_OCCURENCE;
	}
      }
    
      #ifndef SILENT
      printf("Success: Computation %d/%d terminated.\n", i + 1, ITER);
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

    free(storage);
    fclose(output);
    free(path);
  }
  
  return status;
} /* end of main */
