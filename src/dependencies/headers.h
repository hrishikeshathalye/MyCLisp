#define LASSERT(args, cond, fmt, ...)\
if (!(cond)) { \
    lval * err = lval_err(fmt, ##__VA_ARGS__); \
    lval_del(args); \
    return err; \
}

#define LASSERT_TYPE(func, args, index, expect)\
LASSERT(args, args -> cell[index] -> type == expect, \
    "Function '%s' passed incorrect type for argument %d. Got %s, Expected %s.", \
    func, index, ltype_name(args -> cell[index] -> type), ltype_name(expect))

# define LASSERT_NUM(func, args, num)\
LASSERT(args, args -> count == num, \
    "Function '%s' passed incorrect number of arguments. Got %d, Expected %d.", \
    func, args -> count, num)

# define LASSERT_NOT_EMPTY(func, args, index)\
LASSERT(args, args -> cell[index] -> count != 0, \
    "Function '%s' passed {} for argument %d.", func, index);

#include<string.h>

/* Create Enumeration of Possible lval Types */
enum {
    LVAL_ERR,
    LVAL_NUM,
    LVAL_SYM,
    LVAL_STR,
    LVAL_FUN,
    LVAL_SEXPR,
    LVAL_QEXPR
};
mpc_parser_t* Number;
mpc_parser_t* Symbol;
mpc_parser_t* Expr;
mpc_parser_t* MyCLisp;
mpc_parser_t* Sexpr;
mpc_parser_t* Qexpr;
mpc_parser_t* String;
mpc_parser_t* Comment;
struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;
typedef lval*(*lbuiltin)(lenv* , lval* );
struct lval {
    int type;
    double num;
    /* Error and Symbol types have some string data */
    char* err;
    char* sym;
    char* str;
    /* Count and Pointer to a list of "lval*" */
    lbuiltin builtin;
    lenv* env;
    lval* formals;
    lval* body;
    int count;
    lval** cell;
};
struct lenv {
    lenv* par; //parent environment
    int count;
    char** syms;
    lval** vals;
};
lval* lval_eval_sexpr(lenv* , lval*);
lval* lval_eval(lenv* , lval* );
void lval_expr_print(lval* , char, char);
lval* lval_add(lval* , lval* );
lval* lval_read(mpc_ast_t* );
lval* lval_read_num(mpc_ast_t* );
void lval_del(lval* v);
lval* lval_sym(char* );
lval* lval_err(char* , ...);
lval* lval_num(double);
lval* lval_sexpr(void);
void lval_print(lval * );
void lval_println(lval * );
lval* lval_pop(lval * , int);;
lval* lval_take(lval * , int);
lval* builtin_op(lenv * , lval * , char * );
lval* builtin_head(lenv * , lval * );
lval* builtin_tail(lenv * , lval * );
lval* builtin_list(lenv * , lval * );
lval* builtin_eval(lenv * , lval * );
lval* builtin_join(lenv * , lval * );
lval* lval_join(lval * , lval * );
lval* lval_fun(lbuiltin);
lval* lval_copy(lval * );
lenv* lenv_new(void);
void lenv_del(lenv * );
lval* lenv_get(lenv * , lval * );
void lenv_put(lenv * , lval * , lval * );
lval* builtin_add(lenv * , lval * );
lval* builtin_sub(lenv * , lval * );
lval* builtin_mul(lenv * , lval * );
lval* builtin_div(lenv * , lval * );
lval* builtin_def(lenv * , lval * );
void lenv_add_builtins(lenv * );
char* ltype_name(int);
lval* lval_lambda(lval * , lval * );
lval* builtin_lambda(lenv * , lval * );
lenv* lenv_copy(lenv * );
void lenv_def(lenv * , lval * , lval * );
lval* builtin_def(lenv * , lval * );
lval* builtin_put(lenv * , lval * );
lval* builtin_var(lenv * , lval * , char * );
lval* lval_call(lenv * , lval * , lval * );
/*Conditionals*/
lval* builtin_gt(lenv * , lval * );
lval* builtin_lt(lenv * , lval * );
lval* builtin_ge(lenv * , lval * );
lval* builtin_le(lenv * e, lval * );
lval* builtin_ord(lenv * , lval * , char * );
int lval_eq(lval * , lval * );
lval* builtin_cmp(lenv * , lval * , char * );
lval* builtin_eq(lenv * , lval * );
lval* builtin_ne(lenv * , lval * );
lval* builtin_if(lenv * , lval * );
/*Strings*/
lval* lval_str(char * );
void lval_print_str(lval * );
lval* lval_read_str(mpc_ast_t * t);
lval* builtin_load(lenv * , lval * );
lval* builtin_print(lenv * , lval * );
lval* builtin_error(lenv * , lval * );
lval* lval_builtin(lbuiltin);
