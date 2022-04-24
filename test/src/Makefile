CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wfatal-errors -O

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OUTPUTDIR=../obj/
TARGET=obj


all: $(TARGET)

obj: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(OUTPUTDIR)$@
