/*
 * Filename: test_data_manipulation.c
 *
 * Summary: Unitary tests built for data manipulation with libsds.
 *
 * The libsds library may be used to easily abstract some data
 * type. The goal of the data manipulation functions is to take
 * advantage of this abstraction in order to serialize numercial data
 * in CSV files.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-05-15
 *
 * License: see LICENSE file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../src/data_manipulation.h"
#include "../../src/libsds/sds.h"


static char *
format_string_from_sds(sds *atom)
{
  /* MUST BE FREE'D ! 
   *
   * Returns the format string used to print the sds content. 
   *
   * The format string is used by printf family's functions, see the
   * man page ('man 3 printf' on Linux) for more info.
   */
  
  generic_t atom_type = atom->type;
  char *format_string = malloc(6 * sizeof *format_string);
  
  char prec[4];
  data_t data_type;

  if (atom_type == UNIT)
  {
    data_type = (atom->unit).type;
  }
  else if (atom_type == ARRAY)
  {
    data_type = (atom->array).type;
  }
  else
  {
    return NULL;
  }
  
  switch (data_type)
  {
  case INT:
    strcpy(format_string, "%d");
    break;

  case UINT:
    strcpy(format_string, "%d");
    break;

  case DOUBLE:
    snprintf(prec, 4, "%d", atom->precision);
    strcpy(format_string, "%.");
    strcat(format_string, prec);
    strcat(format_string, "f");
    break;

  default:
    return NULL;
  } /* end of first switch-condition */

  return format_string;
} /* end of sds_format_string function */


int
print_sds_in_csv(FILE *output, csv_format format, sds *atom)
{
  /*
   * Print the content stored in a valid sds atom into a file,
   * following chosen CSV format.
   */

  if (output != NULL)
  {
    generic_t atom_type = atom->type;
    
    char sep[3];

    if (atom_type != UNIT && atom_type != ARRAY)
    {
      return SDS_ERR_TYPE;
    } /* end of if-condition */
    
    switch (format)
    {
    case SINGLE_SPACE:
      strcpy(sep, " ");
      break;

    case DOUBLE_SPACE:
      strcpy(sep, "  ");
      break;

    case COMMA:
      strcpy(sep, ",");
      break;

    case SEMICOLON:
      strcpy(sep, ";");
      break;
    } /* end of switch-condition */

    if (atom_type == UNIT && format_string_from_sds(atom) != NULL)
    {
      data_t data_type = (atom->unit).type;

      switch (data_type)
      {
      case INT:
	fprintf(output, format_string_from_sds(atom), (atom->unit)._int);
	break;

      case UINT:
	fprintf(output, format_string_from_sds(atom), (atom->unit)._uint);
	break;

      case DOUBLE:
	fprintf(output, format_string_from_sds(atom), (atom->unit)._double);
	break;
      } /* end of switch-condition */
    
      fprintf(output, sep);
      
      return fprintf(output, "\n");
    } /* end of if-condition */

    if (atom_type == ARRAY && format_string_from_sds(atom) != NULL)
    {
      data_t data_type = (atom->array).type;

      switch (data_type)
      {
      case INT:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, format_string_from_sds(atom), (atom->array)._int[j]);
	  fprintf(output, sep);
	}
	break;
	
      case UINT:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, format_string_from_sds(atom), (atom->array)._uint[j]);
	  fprintf(output, sep);
	}
	break;

      case DOUBLE:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, format_string_from_sds(atom),
		  (atom->array)._double[j]);
	  fprintf(output, sep);
	}
	break;
      } /* end of switch-condition */
    
      return fprintf(output, "\n");
    } /* end of if-condition */
    
    return -2;
  } /* end of if-condition */

  return -1;
} /* end of store_in_csv function */


void
test_format_string_from_sds(void)
{
  const unsigned int bufsz = 6;
  unsigned int flag = 0;
  
  char *fstr;
  sds *atom;

  atom = init_sds();

  printf("TESTING \"UNIT\" SDS TYPE... ");
 
  /* atom_type: UNIT */
  /* data_type: INT */
  sds_store_unit_int(atom, -1);
  fstr = format_string_from_sds(atom);

  if (fstr == NULL)
  {
    flag = -1;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  if (strncmp(fstr, "%d", bufsz))
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  /* data_type: UINT */
  sds_store_unit_uint(atom, 2);
  fstr = format_string_from_sds(atom);

  if (strncmp(fstr, "%d", bufsz))
  {
    flag = 2;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  /* data_type: DOUBLE */
  sds_store_unit_double(atom, 3.14);
  fstr = format_string_from_sds(atom);

  if (strncmp(fstr, "%.10f", bufsz))
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  printf("SUCCESS\nTESTING \"ARRAY\" SDS TYPE... ");

  /* atom_type: ARRAY */
  int int_arr[3] = {-1, 3, -4};
  unsigned int uint_arr[3] = {2, 8, 14};
  double double_arr[3] = {1.41, 2.72, 3.14};
  
  /* data_type: INT */
  sds_store_array_int(atom, int_arr, 3);
  fstr = format_string_from_sds(atom);

  if (strncmp(fstr, "%d", bufsz))
  {
    flag = 4;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  /* data_type: UINT */
  sds_store_array_uint(atom, uint_arr, 3);
  fstr = format_string_from_sds(atom);

  if (strncmp(fstr, "%d", bufsz))
  {
    flag = 5;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  /* data_type: DOUBLE */
  sds_store_array_double(atom, double_arr, 3);
  fstr = format_string_from_sds(atom);

  if (strncmp(fstr, "%.10f", bufsz))
  {
    flag = 6;
    printf("FAILURE (%d)\n", flag);
    free(fstr);
    free(atom);
    return;
  }

  printf("SUCCESS\n");
  
  free(fstr);
  free(atom);

  return;
} /* end of test_format_string_from_sds function */


void
test_print_sds_in_csv(void)
{
  int int_arr[3] = {-1, 3, -4};
  unsigned int uint_arr[3] = {2, 8, 14};
  double double_arr[3] = {1.41, 2.72, 3.14};
  
  unsigned int flag = 0;
  sds *atom = init_sds();
  FILE *output = fopen("print.csv", "w");

  char line[1000];
  FILE *input;

  /* atom_type: UNIT */
  /* data_type: INT */
  sds_store_unit_int(atom, -1);
  print_sds_in_csv(output, COMMA, atom);

  /* data_type: UINT */
  sds_store_unit_uint(atom, 2);
  print_sds_in_csv(output, COMMA, atom);

  /* data_type: DOUBLE */
  sds_store_unit_double(atom, 3.14);
  print_sds_in_csv(output, COMMA, atom);

  /* atom_type: ARRAY */  
  /* data_type: INT */
  sds_store_array_int(atom, int_arr, 3);
  print_sds_in_csv(output, COMMA, atom);

  /* data_type: UINT */
  sds_store_array_uint(atom, uint_arr, 3);
  print_sds_in_csv(output, COMMA, atom);

  /* data_type: DOUBLE */
  sds_store_array_double(atom, double_arr, 3);
  print_sds_in_csv(output, COMMA, atom);

  fclose(output);
  input = fopen("print.csv", "r"); /* closing and reopening just to be
				      sure to have a stream positioned
				      at the beginning of the file */
  
  printf("TESTING STORAGE FOR \"UNIT\" SDS TYPE... ");
  
  /* Tests for UNIT */
  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 1;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "-1,\n", sizeof line))
  {
    flag = 2;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }
  
  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 3;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "2,\n", sizeof line))
  {
    flag = 4;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }
  
  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 5;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "3.1400000000,\n", sizeof line))
  {
    flag = 6;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  printf("SUCCESS\nTESTING STORAGE FOR \"ARRAY\" SDS TYPE... ");

  /* Tests for ARRAY */
  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 7;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "-1,3,-4,\n", sizeof line))
  {
    flag = 8;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 9;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "2,8,14,\n", sizeof line))
  {
    flag = 10;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }
  
  if(fgets(line, sizeof line, input) == NULL)
  {
    flag = 11;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  if (strncmp(line, "1.4100000000,2.7200000000,3.1400000000,\n", sizeof line))
  {
    flag = 12;
    printf("FAILURE (%d)\n", flag);
    free(atom);
    fclose(output);
    return;
  }

  printf("SUCCESS\n");
  
  free(atom);
  fclose(output);
  
  return;
} /* end of test_print_sds_in_csv function */
