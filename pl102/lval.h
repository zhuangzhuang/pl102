#pragma once

#include "mpc\mpc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
	LVAL_NUM,
	LVAL_ERR,
	LVAL_SYM,
	LVAL_SEXPR,
	LVAL_QEXPR
};

typedef struct lval{
	int type;
	long num;
	char* err;
	char* sym;

	int count;
	struct lval** cell;
} lval;


lval* lval_num(long x);
lval* lval_err(char* m);
lval* lval_sym(char* s);

lval* lval_qexpr(void);
lval* lval_sexpr(void);
void lval_del(lval* v);


// build
lval* lval_read(mpc_ast_t* t);

// methods
lval* lval_add(lval* self, lval* x);
lval* lval_pop(lval* self, int i);
lval* lval_take(lval* self, int i);
lval* lval_join(lval* x, lval* y);

// print
void lval_print(lval* v);
void lval_println(lval* v);

// eval
lval* lval_eval(lval* v);

#ifdef __cplusplus
}
#endif
