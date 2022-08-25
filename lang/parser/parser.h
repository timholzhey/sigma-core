//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_PARSER_H
#define SIGMA_CORE_PARSER_H

#include "lang_def.h"

retval_t lang_parse(token_t *tokens, int num_tokens, ast_node_t *ast);

typedef enum {
	PARSER_ERROR_OK,
	PARSER_ERROR_TOKENS_NULL,
	PARSER_ERROR_AST_NULL,
	PARSER_ERROR_NO_TOKENS,
	PARSER_ERROR_MALLOC,
	PARSER_ERROR_UNEXPECTED_TOKEN,
	PARSER_ERROR_SURROUNDING_MISMATCH,
	PARSER_ERROR_UNCLOSED_SCOPE,
} parser_error_t;

parser_error_t parser_errno();

#endif //SIGMA_CORE_PARSER_H
