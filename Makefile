
CC=gcc
DEPS = pdp.h
OBJ =  pdp11_mem.o pdp_test.o r-w_func.o cmd.o run.o

LIBS = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


result_file.c: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)	
	
