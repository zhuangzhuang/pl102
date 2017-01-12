#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include <editline\readline.h>
#include "mpc\mpc.h"

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


long eval_op(long x, char* op, long y) {
	if (strcmp(op, "+") == 0) {
		return x + y;
	}
	if (strcmp(op, "-") == 0) {
		return x - y;
	}
	if (strcmp(op, "*") == 0) {
		return x * y;
	}
	if (strcmp(op, "/") == 0) {
		return x / y;
	}

	return 0;
}


long eval(mpc_ast_t* t) {
	if (strstr(t->tag, "number")) {
		return atoi(t->contents);
	}

	char* op = t->children[1]->contents;
	long x = eval(t->children[2]);
	
	int i = 3;
	while (strstr(t->children[i]->tag, "expr")) {
		x = eval_op(x, op, eval(t->children[i]));
		i++;
	}
	return x;
}


int main(int argc, char** argv) {
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");

	const char *grammar = readfile("lispy.g");
	mpca_lang(MPCA_LANG_DEFAULT, grammar, Number, Operator, Expr, Lispy);


	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c or Enter 'exit' to Exit\n");
	
	mpc_result_t r;

	while (1) {
		char* input = readline("lispy>");
		add_history(input);
		//printf("No you're a %s", input);
		if (stricmp(input, "exit") == 0) {
			break;
		}

		if (mpc_parse("<stdin>", input, Lispy, &r)) {
			//mpc_ast_print(r.output);
			long result = eval(r.output);
			printf("%li\n", result);
			mpc_ast_delete(r.output);
		}
		else
		{
			mpc_err_print(r.error);
			mpc_err_delete(r.error);
		}
		free(input);
	}

	mpc_cleanup(4, Number, Operator, Expr, Lispy);
	free(grammar);
	return 0;
}

