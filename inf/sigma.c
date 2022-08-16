//
// Created by Tim Holzhey on 16.08.22.
//

#include <printf.h>
#include "sigma.h"
#include "lang_def.h"
#include "lexer.h"

#define MAX_TOKENS 1000

const char *derive(const char *func, char var) {
	token_t tokens[MAX_TOKENS];
	lexer_set_var(var);
	int lex_ret = lexer_lex(func, tokens);
	if (lex_ret != RETVAL_OK) {
		printf("Error: lexer_lex returned %d\n", lex_ret);
	}

	// TODO

	return "";
}