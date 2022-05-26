/*
 * Filename: data_manipulation.c
 *
 * Summary: implements basic function to store and plot data.
 *
 * Provides a function to store data from an array to a CSV file, and
 * a function to plot data from an 1-dimensional or a 2-dimensional
 * array using gnuplot.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation date: 2022-04-30
 *
 * License: see LICENSE file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "data_manipulation.h"


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
    char *fs_sds = format_string_from_sds(atom);
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

      
    if (atom_type == UNIT && fs_sds != NULL)
    {
      data_t data_type = (atom->unit).type;

      switch (data_type)
      {
      case INT:
	fprintf(output, fs_sds, (atom->unit)._int);
	break;

      case UINT:
	fprintf(output, fs_sds, (atom->unit)._uint);
	break;

      case DOUBLE:
	fprintf(output, fs_sds, (atom->unit)._double);
	break;
      } /* end of switch-condition */
    
      fprintf(output, sep);

      free(fs_sds);
      return fprintf(output, "\n");
    } /* end of if-condition */

    if (atom_type == ARRAY && fs_sds != NULL)
    {
      data_t data_type = (atom->array).type;

      switch (data_type)
      {
      case INT:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, fs_sds, (atom->array)._int[j]);
	  fprintf(output, sep);
	}
	break;
	
      case UINT:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, fs_sds, (atom->array)._uint[j]);
	  fprintf(output, sep);
	}
	break;

      case DOUBLE:
	for (unsigned int j = 0; j < (atom->array).size; ++j)
	{
	  fprintf(output, fs_sds, (atom->array)._double[j]);
	  fprintf(output, sep);
	}
	break;
      } /* end of switch-condition */

      free(fs_sds);
      return fprintf(output, "\n");
    } /* end of if-condition */

    free(fs_sds);
    return SDS_NULL_FORMAT_STRING;
  } /* end of if-condition */

  return NULL_FILE_DESCRIPTOR;
} /* end of store_in_csv function */
