//
// Created by Tim Holzhey on 16.08.22.
//

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "logging.h"

static struct {
	parser_error_t error;
} m_parser;

#define PARSER_FAIL_WITH_MSG(...) { \
	log_error_noterm("Parser failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

#define PARSER_HANDLE_MALLOC(expr) { \
	if ((expr) == NULL) { \
    	PARSER_FAIL_WITH_MSG("Malloc returned NULL"); \
	} \
}

retval_t parser_parse(token_t *tokens, int num_tokens, ast_node_t *ast) {
	m_parser.error = PARSER_ERROR_OK;

	if (num_tokens == 0) {
		m_parser.error = PARSER_ERROR_NO_TOKENS;
		PARSER_FAIL_WITH_MSG("No tokens provided");
	}

	if (tokens == NULL) {
		m_parser.error = PARSER_ERROR_TOKENS_NULL;
		PARSER_FAIL_WITH_MSG("Tokens are NULL");
	}

	if (ast == NULL) {
		m_parser.error = PARSER_ERROR_MALLOC;
		PARSER_HANDLE_MALLOC(ast = malloc(sizeof(ast_node_t)));
	}

	ast_node_t *current = ast;

	for (int token_pos = 0; token_pos < num_tokens; token_pos++) {

	}

	return RETVAL_OK;
}

parser_error_t parser_errno() {
	return m_parser.error;
}
