/*
 * Filename: main.c
 *
 * Summary: main testing file.
 *
 * Author: jovian <altjovian@netc.eu>
 *
 * Creation date: 2022-04-18
 *
 * License: see LICENSE file.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "test_deterministic_integration.h"
#include "test_brownian.h"
#include "test_numerical_approximation.h"

int
main(void)
{
  srand((unsigned int)time(0));

  double testing_values[12] = {0.0, -5.0, 18.0, sqrt(2),\
    M_PI, 0.00001, 1.0/16.0, 1.0/2048.0, 1.0, 0.6, 0.99999, M_E / 3};

  FILE *triangle_f, *schauder_f, *normal_f;

  
  printf("===== BEGINNING OF \"main.c\" PROGRAM =====\n");

  triangle_f = fopen("triangle.csv", "w");
  schauder_f = fopen("schauder.csv", "w");
  normal_f = fopen("normal.csv", "w");

  if (triangle_f == NULL \
      || schauder_f == NULL \
      || normal_f == NULL) {
    printf("I/O Error. Abort.\n");
    return -1;
  }
  
  printf("Testing function: triangle(double) -> double\n");
  printf("Tested Value\t||\tTriangle\n");

  fprintf(triangle_f, "Tested Value,Result\n");
  
  for (unsigned int j = 0; j < 12; ++j) {
    printf("%+.5f\t||\t%+.5f\n", testing_values[j], triangle(testing_values[j]));
    
    fprintf(triangle_f, "%.5f,%.5f\n", testing_values[j], \
	    triangle(testing_values[j]));
  } /* end of for-loop */

  
  printf("\t===\t\n");

  
  printf("Testing function: ");
  printf("schauder_basis(unsigned int, unsigned int, double) -> double\n");
  printf("Tested value\t||\tSchauder\n");

  fprintf(schauder_f, "Scale,Shift,Tested Value,Result\n");
  
  for (unsigned int j = 0; j < 12; ++j) {

    for (unsigned int k = 0; k < pow(2, j); ++k) {

      for (unsigned int l = 0; l < 12; ++l) {
	printf("(%d,%d,%+.5f)\t||\t%+.5f\n", j, k, \
	       testing_values[l], schauder_basis(j, k, testing_values[l]));
	fprintf(schauder_f, "%d,%d,%.5f,%.5f\n", j, k, \
		testing_values[l], schauder_basis(j, k, testing_values[l]));
      } /* end of third level for-loop */
      
    } /* end of second level for-loop */
    
  } /* end of first level for-loop */

  
  printf("\t===\t\n");

  
  printf("Testing function: rand_normal(void) -> double\n");
  printf("Iteration\t||\tValue\n");

  fprintf(normal_f, "Iteration,Value\n");
  
  for (unsigned int j = 0; j < 10000; ++j) {
    printf("%d\t||\t%+.5f\n", j, rand_normal());
    fprintf(normal_f, "%d,%.5f\n", j, rand_normal());
  } /* end of for-loop */


  printf("\t===\t\n");  
  
  fclose(triangle_f);
  fclose(schauder_f);
  fclose(normal_f);
  
  printf("======== END OF \"main.c\" PROGRAM ========\n");

  return 0;
} /* end of main function */
