#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

void handle_doge() {
	mpc_parser_t* Adjective = mpc_or(4,
		mpc_sym("wow"), mpc_sym("may"),
		mpc_sym("so"), mpc_sym("such"));

	mpc_parser_t* Noun = mpc_or(5,
		mpc_sym("lisp"), mpc_sym("language"),
		mpc_sym("book"), mpc_sym("build"),
		mpc_sym("c")
	);

	mpc_parser_t* Phrase = mpc_and(2, mpcf_strfold,
		Adjective, Noun, free);

	mpc_parser_t* Doge = mpc_many(mpcf_strfold, Phrase);
}

void gen_doge() {
	mpc_parser_t* Adjective = mpc_new("adjective");
	mpc_parser_t* Noun = mpc_new("noun");
	mpc_parser_t* Phrase = mpc_new("phrase");
	mpc_parser_t* Doge = mpc_new("doge");

	const char* gramar = readfile("g.txt");
	mpca_lang(MPCA_LANG_DEFAULT, gramar, Adjective, Noun, Phrase, Doge);


	mpc_cleanup(4, Adjective, Noun, Phrase, Doge);
	free(gramar);
}

int main(int argc, char** argv) {
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+c to Exit\n");

	while (1) {
		char* input = readline("lispy>");
		add_history(input);
		printf("No you're a %s", input);
		free(input);
	}
	return 0;
}

