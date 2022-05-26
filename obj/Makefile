CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wfatal-errors -std=c11
LDFLAGS=-L../libsds/ -lm -lsds

OUTPUTDIR=../bin/
OBJ=$(wildcard *.o)
TARGET=compute_approximation.exe


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUTPUTDIR)$@ $^ $(LDFLAGS)
