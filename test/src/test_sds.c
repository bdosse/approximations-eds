#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/sds.h"


void
test_generic_unit(void)
{
  struct generic_unit ngu = {.type = INT, ._int = -2};  
  unsigned int flag = 0;
  
  struct generic_unit gu;
  
  printf("Testing generic unit:... ");
  
  if (ngu.type != INT || ngu._int != -2)
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    return;
  }
  
  gu.type = INT;
  gu._int = 1;

  if (gu.type != INT || gu._int != 1)
  {
    flag = 2;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  gu.type = DOUBLE;
  gu._double = 2.0;

  if (gu.type != DOUBLE || gu._double != 2.0)
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  gu.type = UINT;
  gu._uint = 3;

  if (gu.type != UINT || gu._uint != 3)
  {
    flag = 4;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  gu.type = INT;
  gu._int = -1;

  if (gu.type != INT || gu._int != -1)
  {
    flag = 5;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  ngu.type = DOUBLE;
  ngu._double = -2.0;
  
  if (ngu.type != DOUBLE || ngu._double != -2.0)
  {
    flag = 6;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  if (flag)
  {
    printf("FAILURE (%d)\n", flag + 1);
  }
  else
  {
    printf("SUCCESS\n");
  }
} /* end of test_generic_unit function */


void
test_generic_array(void)
{
  unsigned int flag = 0;
  int int_arr[3] = {1, -2, 3};
  unsigned int uint_arr[3] = {4, 7, 6};
  struct generic_array nga = {.type = INT, .size = 3, ._int = int_arr};
  
  struct generic_array ga;
  unsigned int s;

  printf("Testing generic array:... ");

  if (nga.type != INT || nga.size != 3 || nga._int != int_arr)
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if (nga._int[j] != int_arr[j])
    {
      flag = 2;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }

  nga.type = UINT;
  nga._uint = uint_arr;

  if (nga.type != UINT || nga._uint != uint_arr)
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  s = 3;
  double *double_arr = malloc(s * sizeof *double_arr);

  double_arr[0] = -3.2;
  double_arr[1] = 7.009;
  double_arr[2] = 9.0*9.0;
  
  ga.type = DOUBLE;
  ga.size = s;
  ga._double = double_arr;

  if (ga.type != DOUBLE || ga.size != 3 || ga._double != double_arr)
  {
    flag = 4;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if (ga._double[j] != double_arr[j])
    {
      flag = 5;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }

  s = 4;
  unsigned int *uint_arr_4 = malloc(s * sizeof *uint_arr_4);
  uint_arr_4[0] = 0;
  uint_arr_4[1] = 9;
  uint_arr_4[2] = 7;
  uint_arr_4[3] = 12;

  ga.type = UINT;
  ga.size = s;
  ga._uint = uint_arr_4;

  if (ga.type != UINT || ga.size != 4 || ga._uint != uint_arr_4)
  {
    flag = 6;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 4; ++j)
  {
    if (ga._uint[j] != uint_arr_4[j])
    {
      flag = 7;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }
  
  if (flag)
  {
    printf("FAILURE (%d)\n", flag);
  }
  else
  {
    printf("SUCCESS\n");
  }

  
  free(double_arr);
  free(uint_arr_4);
} /* end of test_generic_array function */


void
test_sds_unit(void)
{
  unsigned int flag = 0;
  sds *ns = init_sds();

  sds *s;
  struct generic_unit gu;
  
  printf("Testing unit SDS:... ");

  if (ns->type != UNDEF || ns->precision != 10)
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  s = malloc(sizeof *s);
  s->type = UNDEF;
  s->precision = 10;

  if (s->type != UNDEF || s->precision != 10)
  {
    flag = 2;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  gu.type = INT;
  gu._int = 1;

  s->type = UNIT;
  s->unit = gu;

  if (s->type != UNIT || (s->unit).type != INT || (s->unit)._int != 1)
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  sds_store_unit_uint(s, 3);

  if (s->type != UNIT || (s->unit).type != UINT || (s->unit)._uint != 3)
  {
    flag = 5;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  sds_store_unit_double(ns, -4.2);

  if (ns->type != UNIT || (ns->unit).type != DOUBLE || (ns->unit)._double != -4.2)
  {
    flag = 6;
    printf("FAILURE (%d)\n", flag);
    return;
  }
  
  if (flag)
  {
    printf("FAILURE (%d)\n", flag);
  }
  else
  {
    printf("SUCCESS\n");
  }

  free(ns);
  free(s);
} /* end of test_sds_unit function */


void
test_sds_array(void)
{
  unsigned int flag = 0;
  sds *s = init_sds();
  unsigned int n = 3;
  int *int_arr_p = malloc(n * sizeof *int_arr_p);
  unsigned int *uint_arr_p = malloc(n * sizeof *uint_arr_p);
  double *double_arr_p = malloc(n * sizeof *double_arr_p);

  printf("Testing array SDS:... ");

  int_arr_p[0] = -1;
  int_arr_p[1] = 3;
  int_arr_p[2] = -2;

  uint_arr_p[0] = 7;
  uint_arr_p[1] = 12;
  uint_arr_p[2] = 3;

  double_arr_p[0] = -2.7347890643;
  double_arr_p[1] = 8.1;
  double_arr_p[2] = 99.0;

  sds_store_array_int(s, int_arr_p, n);

  if (s->type != ARRAY || (s->array).size != 3 || (s->array).type != INT)
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if ((s->array)._int[j] != int_arr_p[j])
    {
      flag = 2;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }

  sds_store_array_uint(s, uint_arr_p, n);

  if (s->type != ARRAY || (s->array).size != 3 || (s->array).type != UINT)
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if ((s->array)._uint[j] != uint_arr_p[j])
    {
      flag = 4;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }

  sds_store_array_double(s, double_arr_p, n);
  
  if (s->type != ARRAY || (s->array).size != 3 || (s->array).type != DOUBLE)
  {
    flag = 5;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if ((s->array)._double[j] != double_arr_p[j])
    {
      flag = 6;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }

  double_arr_p[0] = -8.8;
  double_arr_p[1] = 0.002;
  double_arr_p[2] = 666.0987;

  if (s->type != ARRAY || (s->array).size != 3 || (s->array).type != DOUBLE)
  {
    flag = 7;
    printf("FAILURE (%d)\n", flag);
    return;
  }

  for (unsigned int j = 0; j < 3; ++j)
  {
    if ((s->array)._double[j] != double_arr_p[j])
    {
      flag = 8;
      printf("FAILURE (%d)\n", flag);
      return;
    }
  }
  
  if (flag)
  {
    printf("FAILURE (%d)\n", flag);
  }
  else
  {
    printf("SUCCESS\n");
  }

  free(s);
  free(int_arr_p);
  free(uint_arr_p);
  free(double_arr_p);
} /* end of test_sds_array function */
