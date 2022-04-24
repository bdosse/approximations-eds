CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wfatal-errors
LDFLAGS=-lm

OUTPUTDIR=../bin/
OBJ=$(wildcard *.o)
TARGET=brownian_path.exe


all: $(TARGET)

brownian_path.exe: $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)$@ $^ $(LDFLAGS)
