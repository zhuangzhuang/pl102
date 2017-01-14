#pragma once

#include "mpc\mpc.h"

#ifdef __cplusplus
extern "C" {
#endif

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

typedef enum lvaltype{
	LVAL_NUM,
	LVAL_ERR,
	LVAL_SYM,
	LVAL_FUN,
	LVAL_SEXPR,
	LVAL_QEXPR
}lvaltype;

typedef lval* (*lbuiltin)(lenv*, lval*);

typedef struct lval{
	lvaltype type;
	long num;
	char* err;
	char* sym;
	lbuiltin fun;

	int count;
	struct lval** cell;
} lval;


lval* lval_num(long x);
lval* lval_err(char* fmt, ...);
lval* lval_sym(char* s);
lval* lval_fun(lbuiltin func);
lval* lval_qexpr(void);
lval* lval_sexpr(void);
void lval_del(lval* v);


// build
lval* lval_read(mpc_ast_t* t);

// methods
lval* lval_add(lval* self, lval* x);
lval* lval_pop(lval* self, int i);
lval* lval_take(lval* self, int i);
lval* lval_join(lval* self, lval* y);
lval* lval_copy(lval* self);

// print
void lval_print(lval* v);
void lval_println(lval* v);


// env
typedef struct lenv {
	int count;
	char** syms;
	lval** vals;
}lenv;


// build
lenv* lenv_new(void);

void lenv_del(lenv* e);

// method
lval* lenv_get(lenv* e, lval* k);
void  lenv_put(lenv* e, lval* k, lval* v);

// builtin
void lenv_add_builtins(lenv* e);

// eval
lval* lval_eval(lenv* e, lval* v);

#ifdef __cplusplus
}
#endif
