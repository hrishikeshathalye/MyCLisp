/*This program implements a basic prompt style input interface for the Lisp Implementation*/
#include <stdio.h>

#include <stdlib.h>

#include <editline/readline.h> /* Included to implement prompt reading and command line history*/

#include <editline/history.h>

#include "mpc.h"

#include "headers.h"

int main(int argc, char ** argv) {
    /*Parsers*/
	Number = mpc_new("number");
    Symbol = mpc_new("symbol");
    Expr = mpc_new("expr");
    MyCLisp = mpc_new("myclisp");
    Sexpr = mpc_new("sexpr");
    Qexpr = mpc_new("qexpr");
    String = mpc_new("string");
    Comment = mpc_new("comment");
    /* Defining the parsers */
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
    number   : /-?[0-9]+(\\.[0-9]+)?/;                             \
    symbol :/[a-zA-Z0-9_+\\-*\\/\\\\=<>!&]+/;   \
    sexpr  : '(' <expr>* ')' ;               \
    qexpr : '{' <expr>* '}' ;                 \
    expr     : <number> | <symbol> | <sexpr> | <qexpr> | <string> | <comment> ; \
    string  : /\"(\\\\.|[^\"])*\"/ ;			\
    comment : /;[^\\r\\n]*/ ;					\
    myclisp    : /^/ <expr>* /$/ ;             \
    ",
    Number, Symbol, Sexpr, Qexpr, Expr, String, Comment, MyCLisp);
    lenv * e = lenv_new();
    lenv_add_builtins(e);
    if (argc == 1) {
        /* Print Version and Exit Information */
        fputs("MyCLisp Version 3.0\n", stdout);
        fputs("Press Ctrl+c to Exit\n", stdout);
        /* In a never ending loop */
        while (1) {

            /* Output our prompt and get input */
            char * input = readline("MyCLisp> ");

            /* Add input to history */
            add_history(input);

            /* Attempt to Parse the user Input */
            mpc_result_t r;
            if (mpc_parse("<stdin>", input, MyCLisp, & r)) {
                /* On Success Print the AST evaluated output */
                lval * x = lval_eval(e, lval_read(r.output));
                lval_println(x);
                lval_del(x);
                mpc_ast_delete(r.output);
            } else {
                /* Otherwise Print the Error */
                mpc_err_print(r.error);
                mpc_err_delete(r.error);
            }

            /* Free retrived input */
            free(input);
        }
    }
    /* Supplied with list of files */
    if (argc >= 2) {

        /* loop over each supplied filename (starting from 1) */
        for (int i = 1; i < argc; i++) {

            /* Argument list with a single argument, the filename */
            lval * args = lval_add(lval_sexpr(), lval_str(argv[i]));

            /* Pass to builtin load and get the result */
            lval * x = builtin_load(e, args);

            /* If the result is an error be sure to print it */
            if (x -> type == LVAL_ERR) {
                lval_println(x);
            }
            lval_del(x);
        }
    }
    lenv_del(e);
    /*Deleting the parsers*/
    mpc_cleanup(8, Number, Symbol, Sexpr, Qexpr, Expr, String, Comment, MyCLisp);
    return 0;
}
