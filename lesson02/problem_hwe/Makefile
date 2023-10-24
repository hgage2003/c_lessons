CC=gcc
CFLAGS=-I. -O2
DEPS = bit_sieve.h
OBJ = problem_hwe.o bit_sieve.o
LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

problem_hwe.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)