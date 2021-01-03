AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = myclisp
myclisp_SOURCES = src/evaluator.c src/mpc.c src/prompt.c src/dependencies/mpc.h src/dependencies/headers.h src/dependencies/readline.h src/dependencies/history.h 
myclisp_LDADD = -ledit
myclisp_CFLAGS = -I. -Lsrc/dependencies -l:libedit.so
