#ifndef TEST_DETERMINISTIC_INTEGRATION
#define TEST_DETERMINISTIC_INTEGRATION

extern double
integrate(double, double, double (*f)(double));

extern double
identity(double);

extern double
integrate_identity(double, double);

#endif
