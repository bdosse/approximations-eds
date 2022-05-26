# Stochastic Differential Equation: Approximations Method

This project implements the Euler-Maruyama scheme to approximate the
true solution of an Ito stochastic differential equation (SDE).

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
./compute_approximation.exe
```

Without any modification of the source file, the program will compute
the pathwise approximation of an Ito process which is solution of the
Ito SDE:

$$ dX_t = X_tdt + X_tdW_t $$

where $W_t$ is a standard Wiener process. The data are stored in the
`./data/data_1.csv` file. The file may be imported in any data
manipulation program like `R` or `LibreOffice Calc`.


## Configuration

To configure this program, you need to modify the `config.h` file in
the `src` folder, and recompile the program.

The configuration file describes each variable in a meaningful way, so
read the comments carefully before any modification. In particular, it
is in the `config.h` file that you define the functions of your Ito
SDE.


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


## How to help?

There are things I'm unable to do at the moment. Here is a list
of some of them:

- [ ] Implement the Milstein scheme (with numerical differentiation
      utility)
- [ ] Implement a Runge-Kutta scheme (is there something better than
      second strong order of convergence?)
- [ ] Implement something to play with Ito-Taylor expansions
- [ ] Connection with a plotting software like gnuplot


***

## References

KLOEDEN, Peter E. and Eckhard PLATEN. *Numerical Solution of
	Stochastic Differential Equations*. 1st ed. Vol. 23. Berlin :
	Springer, 1992. XXXVI, 636 p. (Applications of Mathematics). ISBN
	978-3-662-12616-5


