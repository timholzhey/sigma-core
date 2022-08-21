//
// Created by Tim Holzhey on 16.08.22.
//

#include <printf.h>
#include "sigma.h"
#include "lang_def.h"
#include "lexer.h"

#define MAX_NUM_TOKENS 1000

const char *retval_string[RETVAL_COUNT] = {
		[RETVAL_OK] = "OK",
		[RETVAL_ERROR] = "Error",
};

const char *derive(const char *func, char var) {
	token_t tokens[MAX_NUM_TOKENS];
	lexer_set_var(var);
	int lex_ret = lexer_lex(func, tokens);
	if (lex_ret != RETVAL_OK) {
		printf("Error: lexer returned %s (%d)\n", retval_string[lex_ret], lex_ret);
	}

	// TODO

	return "";
}