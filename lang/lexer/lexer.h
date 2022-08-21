//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_LEXER_H
#define SIGMA_CORE_LEXER_H

#include "lang_def.h"

void lexer_set_var(char var);

retval_t lexer_lex(const char *input, token_t *tokens);

typedef enum {
	LEXER_ERROR_OK,
	LEXER_ERROR_UNKNOWN_TOKEN,
} lexer_error_t;

lexer_error_t lexer_errno();

#endif //SIGMA_CORE_LEXER_H
