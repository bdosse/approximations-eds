/*
 * Filename: brownian_path.h
 *
 * Summary: defines functionsd allowing to simulate Brownian
 * trajectories.
 *
 * Author: bdj <bdosse(at)student.uliege.be>
 *
 * Creation: 2022-04-03
 *
 * License: see LICENSE file.
 */

#ifndef BROWNIAN_PATH_H
#define BROWNIAN_PATH_H


extern double
rand_normal(void);

extern double *
brownian_path(unsigned int);


#endif /* BROWNIAN_PATH_H */
