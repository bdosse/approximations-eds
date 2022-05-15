# Stochastic Differential Equation: Approximations Method

This project present some approximation for solving famous stochastic
differential equations. The first methods used are the Euler-Maruyama
scheme and the Milstein scheme following the constructions given by
P. Kloeden and E. Platen[^1].

## Building

First, clone the repository:

```
git clone https://github.com/bdosse-jovian/approximations-eds.git
cd approximations-eds
```

[Optional] Make sure everything is OK by compiling unitary test:
```
make test
cd test/bin/
./functional_test.exe
cd ../../
```

Build the project:
```
make
```

Start the calculation:
```
cd bin/
./compute_solution.exe
```

This project may be used to approximate the solution of some simple
enough SDE. Details can be found in the "References" section.

## Equation

By default, the method used by this project is the Milstein
scheme. The program tries to solve the Ornstein–Uhlenbeck equation:

![equation](https://bit.ly/3MlGx98)

## Debug, cleaning, etc.

Enabling debug symbols is made by using the following recipe:

```
make debug
```

In order to get rid of object files:

```
make clean
```

It is possible to get rid of every generated files by issuing:

```
make mrproper
```

***

## References

[^1]: KLOEDEN, Peter E. and Eckhard PLATEN. *Numerical Solution of
    Stochastic Differential Equations*. 1st ed. Vol. 23. Berlin :
    Springer, 1992. XXXVI, 636 p. (Applications of Mathematics). isbn
    978-3-662-12616-5


