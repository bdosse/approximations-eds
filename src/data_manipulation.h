#ifndef DATA_MANIPULATION_H
#define DATA_MANIPULATION_H

#include <stdio.h>

#include "libsds/sds.h"


typedef enum {SINGLE_SPACE=1, DOUBLE_SPACE, COMMA, SEMICOLON} csv_format;

int
print_sds_in_csv(FILE *output, csv_format format, sds *atom);


#endif /* DATA_MANIPULATION_H */
