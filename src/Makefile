CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wfatal-errors

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
OUTPUTDIR=../obj/
TARGET=obj


all: $(TARGET)

debug: CFLAGS += -g3
debug: $(TARGET)

obj: $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(OUTPUTDIR)$@


