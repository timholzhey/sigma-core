//
// Created by Tim Holzhey on 25.08.22.
//

#include <stdlib.h>
#include "stringify.h"
#include "logging.h"
#include "lexer.h"

#define STRINGIFIER_FAIL_WITH_MSG(...) { \
	log_error_noterm("Preprocessor failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

int stringify_node(ast_node_t *ast, char *string, int size_left) {
	int chars_written = 0;

	if (token_flags_map[ast->token.type] & TOKEN_FLAG_SURROUND) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, "%s", token_str_repr_map[ast->token.type]);
	}

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_INFIX) ||
		token_flags_map[ast->token.type] & TOKEN_FLAG_POSTFIX ||
		token_flags_map[ast->token.type] & TOKEN_FLAG_SURROUND) {
		if (ast->left && !(ast->token.type == TOKEN_TYPE_OPERATOR_SUB && ast->left->token.type == TOKEN_TYPE_NUM && ast->left->token.value.number == 0.0f)) {
			chars_written += stringify_node(ast->left, string + chars_written, size_left - chars_written);
		}
	}

	switch (ast->token.type) {
		case TOKEN_TYPE_VAR:
			chars_written += snprintf(string + chars_written, size_left - chars_written, "%c", lexer_get_var());
			break;

		case TOKEN_TYPE_NUM:
			chars_written += snprintf(string + chars_written, size_left - chars_written, "%g", ast->token.value.number);
			break;

		case TOKEN_TYPE_OPERATOR_MUL:
			if (!(ast->left && token_flags_map[ast->left->token.type] & TOKEN_FLAG_IMPL_MULT_AFTER &&
				ast->right && token_flags_map[ast->right->token.type] & TOKEN_FLAG_IMPL_MULT_BEFORE)) {
				chars_written += snprintf(string + chars_written, size_left - chars_written, "%s", token_str_repr_map[ast->token.type]);
			}
			break;

		default:
			chars_written += snprintf(string + chars_written, size_left - chars_written, "%s", token_str_repr_map[ast->token.type]);
			break;
	}

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_PREFIX)) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, "(");
		if (ast->left) {
			chars_written += stringify_node(ast->left, string + chars_written, size_left - chars_written);
		}
	}

	if (ast->right) {
		chars_written += stringify_node(ast->right, string + chars_written, size_left - chars_written);
	}

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_PREFIX)) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, ")");
	}

	return chars_written;
}

retval_t lang_stringify(ast_node_t *ast, char **string, int *str_len) {
	if (*string != NULL) {
		STRINGIFIER_FAIL_WITH_MSG("String output is not null");
	}

	static int max_str_len = 100;
	*string = malloc(max_str_len);
	if (*string == NULL) {
		STRINGIFIER_FAIL_WITH_MSG("Could not allocate memory for string");
	}

	*str_len = stringify_node(ast, *string, max_str_len);

	return RETVAL_OK;
}
