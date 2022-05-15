CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wfatal-errors -O
LDFLAGS=-lm -L../../includes -lsds

OUTPUTDIR=../bin/
OBJ=$(wildcard *.o)
TARGET=bin


all: $(TARGET)

bin:
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)functional_test.exe $(OBJ) $(LDFLAGS)

