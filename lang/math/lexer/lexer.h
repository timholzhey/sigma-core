//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_LEXER_H
#define SIGMA_CORE_LEXER_H

#include "lang_def.h"

void lexer_set_var(char var);

char lexer_get_var();

retval_t lang_lex(const char *input, token_t *tokens, int *num_tokens, int max_num_tokens);

typedef enum {
	LEXER_ERROR_OK,
	LEXER_ERROR_UNKNOWN_TOKEN,
	LEXER_ERROR_INSUFFICIENT_SPACE,
} lexer_error_t;

lexer_error_t lexer_errno();

#endif //SIGMA_CORE_LEXER_H
