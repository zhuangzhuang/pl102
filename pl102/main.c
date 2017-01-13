#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <editline\readline.h>
#include "mpc\mpc.h"

#include "lval.h"


const char* readfile(const char* filename) {
	fpos_t size = 0;
	char* res = 0;
	FILE* fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
	fgetpos(fp, &size);
	res = (char*)malloc(size + 1);
	memset(res, 0, size + 1);
	fseek(fp, 0, SEEK_SET);
	fread(res, size, 1, fp);
	fclose(fp);
	return res;
}

int number_of_nodes(mpc_ast_t* t) {
	if (t->children_num == 0) {
		return 1;
	}
	if (t->children_num >= 1) {
		int total = 1;
		for (int i = 0; i < t->children_num; i++) {
			total = total + number_of_nodes(t->children[i]);
		}
		return total;
	}
	return 0;
}


int main(int argc, char** argv) {
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Symbol = mpc_new("symbol");
	mpc_parser_t* Sexpr = mpc_new("sexpr");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	const char *grammar = readfile("lispy.g");
	mpca_lang(MPCA_LANG_DEFAULT, grammar, 
		Number, Symbol, Sexpr, Expr, Lispy);


	puts("Lispy Version 0.0.0.0.1");
	printf(
"Press Ctrl+c or Enter 'exit' to Exit\n\
 enter :d+ show debug  \n\
 enter :d- close_debug \n                ");
	
	mpc_result_t r;
	int show_tree = 0;

	while (1) {
		char* input = readline("lispy>");
		add_history(input);
		if (stricmp(input, ":exit") == 0) {
			break;
		}
		if (stricmp(input, ":d+") == 0) {
			show_tree = 1;
			continue;
		}
		if (stricmp(input, ":d-") == 0) {
			show_tree = 0;
			continue;
		}
		
		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			lval* tree = lval_read(r.output);
			if (show_tree) {
				lval_println(tree);
			}
			lval* x = lval_eval(tree);
			lval_println(x);
			lval_del(x);
			mpc_ast_delete(r.output);
		}
		else
		{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(input);
	}

	mpc_cleanup(4, Number, Symbol, Sexpr, Expr, Lispy);
	free(grammar);
	return 0;
}

