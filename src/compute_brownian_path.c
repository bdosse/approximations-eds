/*
 * Filename: compute_brownian_path.c
 *
 * Summary: computing different brownian paths.
 *
 * Author: bdj <bdosse@student.uliege.be>
 *
 * Creation date: 2022-04-03
 *
 * License: see LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#include "brownian_path.h"


static int
store_in_csv(FILE *output, double time, double position)
{  
  if (output != NULL) {
    int printed_char = fprintf(output, "%.5f,%.15f,\n", time, position);
    return printed_char;
  }
  
  return -1;
} /* end of store_in_csv function */


int
main(void)
{
  srand((unsigned int)time(0));

  struct stat folder_stat = {0};
  
  if (stat("generated_data", &folder_stat) == -1) {
    mkdir("generated_data", 0700);
  } /* end of if-condition */

  unsigned int BMT_ITERATIONS = 10000;
  unsigned int DONSKER_MAX_STEP = 10000;
  unsigned int SCHAUDER_MAX_STEP = 16;    /* thou shalt not go above 23 */
  unsigned int NAIVE_ITERATIONS = 10000;

  double MAX_TIME = 1.0;
  double TIME_INCREMENT = 0.001;
  
  int return_code;
  double time, position, bmt;
  double *naive_brownian_array;
  
  FILE *output_bmt = fopen("generated_data/data_bmt.csv", "w");
  FILE *output_donsker = fopen("generated_data/data_donsker.csv", "w");
  FILE *output_schauder = fopen("generated_data/data_schauder.csv", "w");
  FILE *output_naive = fopen("generated_data/data_naive.csv", "w");
  
  if (output_bmt == NULL \
      || output_donsker == NULL	 \
      || output_schauder == NULL \
      || output_naive == NULL) {
    printf("Unable to open one of the output files.\nAborting...\n");
    return -1;
  }
  
  printf("===== BEGINNING OF \"compute_brownian_path.c\" PROGRAM =====\n");

  /*************************************************************/
  printf("================ USING: BOX-MULLER TRANSFORM ===============\n");
  printf("VALUE\n");
  fprintf(output_bmt, "VALUE,\n");

  for (unsigned int i = 0; i < BMT_ITERATIONS; ++i) {
    bmt = rand_normal();
    printf("%'.6f\n", bmt);
    fprintf(output_bmt, "%.15f\n", bmt);
  } /* end of for-loop */
  
  /*************************************************************/
  
  printf("================= USING: DONSKER ALGORITHM =================\n");
  printf("TIME\t|\tPOSITION\n");
  fprintf(output_donsker, "Time,Position,\n");

  time = 0.0;
  
  while (time < MAX_TIME) {
    position = donsker_brownian_path(DONSKER_MAX_STEP, time);
    
    printf("%'.3f\t|\t%'.6f\n", time, position);
    return_code = store_in_csv(output_donsker, time, position);
    
    time += TIME_INCREMENT;
  } /* end of while-loop */

  /*************************************************************/

  printf("================ USING: SCHAUDER ALGORITHM =================\n");
  printf("TIME\t|\tPOSITION\n");
  fprintf(output_schauder, "Time,Position,\n");

  time = 0.0;

  while (time < MAX_TIME) {
    position = schauder_brownian_path(SCHAUDER_MAX_STEP, time);
    
    printf("%'.3f\t|\t%'.6f\n", time, position);
    return_code = store_in_csv(output_schauder, time, position);
    
    time += TIME_INCREMENT;
  } /* end of while-loop */
  
  /*************************************************************/

  printf("================== USING: NAIVE ALGORITHM ==================\n");
  printf("TIME\t|\tPOSITION\n");
  fprintf(output_naive, "Time,Position,\n");

  naive_brownian_array = naive_brownian_path(NAIVE_ITERATIONS);

  for (unsigned int i = 0; i < NAIVE_ITERATIONS; ++i) {
    printf("%'.3f\t|\t%'.6f\n", \
	   (double)i / (double)NAIVE_ITERATIONS, \
	   naive_brownian_array[i]);
    return_code = store_in_csv(output_naive, \
			       (double)i / (double)NAIVE_ITERATIONS, \
			       naive_brownian_array[i]);
  } /* end of for-loop */
  
  /*************************************************************/

  fclose(output_bmt);
  fclose(output_donsker);
  fclose(output_schauder);
  fclose(output_naive);

  printf("===== END OF \"compute_brownian_path.c\" PROGRAM =====\n");
  
  return return_code;
} /* end of main */
