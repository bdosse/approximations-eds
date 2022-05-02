/*
 * Filename: sds.c
 *
 * Summary: implements basic data structure to ease storage and
 * plotting.
 *
 * Provides a simple data structure that encapsulates data of type
 * int, unsigned int, and double, as well as array of said data types.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-05-02
 *
 * License: see LICENSE file.
 */

#include <stdlib.h>
#include <sys/stat.h>

#include "sds.h"


sds *
init_sds(void)
{
  sds *default_sds = malloc(sizeof *default_sds);
  default_sds->precision = 10;
  default_sds->type = UNDEF;

  return default_sds;
} /* end of init_sds function */


void
sds_store_unit_int(sds *atom, int item)
{
  struct generic_unit temp = {.type = INT, ._int = item};
  atom->type = UNIT;
  atom->unit = temp;
} /* end of sds_store_unit_int function */


void
sds_store_unit_uint(sds *atom, unsigned int item)
{
  struct generic_unit temp = {.type = UINT, ._uint = item};
  atom->type = UNIT;
  atom->unit = temp;
} /* end of sds_store_unit_uint function */


void
sds_store_unit_double(sds *atom, double item)
{
  struct generic_unit temp = {.type = DOUBLE, ._double = item};
  atom->type = UNIT;
  atom->unit = temp;
} /* end of sds_store_unit_double function */


void
sds_store_array_int(sds *atom, int *arr, unsigned int arr_size)
{
  struct generic_array temp = {.type = INT, .size = arr_size, ._int = arr};
  atom->type = ARRAY;
  atom->array = temp;
} /* end of sds_store_array_int function */


void
sds_store_array_uint(sds *atom, unsigned int *arr, unsigned int arr_size)
{
  struct generic_array temp = {.type = UINT, .size = arr_size, ._uint = arr};
  atom->type = ARRAY;
  atom->array = temp;
} /* end of sds_store_array_uint function */


void
sds_store_array_double(sds *atom, double *arr, unsigned int arr_size)
{
  struct generic_array temp = {.type = DOUBLE, .size = arr_size, ._double = arr};
  atom->type = ARRAY;
  atom->array = temp;
} /* end of sds_store_array_double function */


void
sds_store_precision(sds *atom, unsigned int prec)
{
  atom->precision = prec;
} /* end of sds_store_precision function */
