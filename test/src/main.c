/*
 * Filename: main.c
 *
 * Summary: main testing file.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
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
#include "test_sds.h"
#include "test_data_manipulation.h"

#include "test_numerical_approximation.h"

int
main(void)
{
  printf("===== BEGINNING OF \"main.c\" PROGRAM =====\n");

  /* Testing SDS related functions */
  test_generic_unit();
  test_generic_array();
  test_sds_unit();
  test_sds_array();

  /* Testing data manipulation functions */
  test_format_string_from_sds();
  test_print_sds_in_csv();
  
  printf("======== END OF \"main.c\" PROGRAM ========\n");

  return 0;
} /* end of main function */
