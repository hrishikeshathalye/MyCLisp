CC=gcc
CFLAGS=-I.
DEPS = mpc.h headers.h
OBJ = evaluator.o prompt.o mpc.o 

%.o: %.c $(DEPS)
	$(CC) -ledit -c -o $@ $< $(CFLAGS)

MyCLisp: $(OBJ)
	$(CC) -ledit -o $@ $^ $(CFLAGS) -ledit

clean:
	rm -f *.o MyCLisp
