CC=gcc
CFLAGS=-I. -Ldependencies -l:libedit.so
DEPS = dependencies/mpc.h dependencies/headers.h dependencies/readline.h dependencies/history.h
OBJ = evaluator.o prompt.o mpc.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MyCLisp: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o MyCLisp
