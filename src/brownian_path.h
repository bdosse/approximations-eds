#ifndef BROWNIAN_PATH_H
#define BROWNIAN_PATH_H

#include <math.h>


extern double
rand_normal(void);

extern double
schauder_brownian_path(unsigned int, double);

extern double
donsker_brownian_path(unsigned int, double);

extern double *
naive_brownian_path(unsigned int);


#endif /* BROWNIAN_PATH_H */
