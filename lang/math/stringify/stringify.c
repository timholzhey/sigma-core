//
// Created by Tim Holzhey on 25.08.22.
//

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stringify.h"
#include "logging.h"
#include "lexer.h"

#define STRINGIFIER_FAIL_WITH_MSG(...) { \
	log_error_noterm("Preprocessor failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

static struct {
	bool is_error;
	char error_desc[TOKEN_MAX_STR_IDENT_LENGTH];
	int error_desc_len;
} m_stringify;

int stringify_node(ast_node_t *ast, char *string, int size_left) {
	int chars_written = 0;

	if (token_flags_map[ast->token.type] & TOKEN_FLAG_SURROUND) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, "%s", token_str_repr_map[ast->token.type]);
	}

	bool paren_precedence = false;
	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_INFIX) && ast->left &&
		token_precedence_map[ast->token.type] <= token_precedence_map[ast->left->token.type] &&
		token_precedence_map[ast->left->token.type] != TOKEN_PRECEDENCE_NONE &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_ADD && ast->left->token.type == TOKEN_TYPE_OPERATOR_ADD) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_ADD && ast->left->token.type == TOKEN_TYPE_OPERATOR_SUB) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_SUB && ast->left->token.type == TOKEN_TYPE_OPERATOR_ADD) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_MUL && ast->left->token.type == TOKEN_TYPE_OPERATOR_MUL)) {
		paren_precedence = true;
		chars_written += snprintf(string + chars_written, size_left - chars_written, "(");
	}

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_INFIX) ||
		token_flags_map[ast->token.type] & TOKEN_FLAG_POSTFIX ||
		token_flags_map[ast->token.type] & TOKEN_FLAG_SURROUND) {
		if (ast->left && !(ast->token.type == TOKEN_TYPE_OPERATOR_SUB && ast->left->token.type == TOKEN_TYPE_NUM &&
						   ast->left->token.value.number == 0.0f)) {
			chars_written += stringify_node(ast->left, string + chars_written, size_left - chars_written);
		}
	}

	if (paren_precedence) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, ")");
		paren_precedence = false;
	}

	switch (ast->token.type) {
		case TOKEN_TYPE_VAR:
			chars_written += snprintf(string + chars_written, size_left - chars_written, "%c", lexer_get_var());
			break;

		case TOKEN_TYPE_NUM:
			chars_written += snprintf(string + chars_written, size_left - chars_written, "%g", ast->token.value.number);
			break;

		case TOKEN_TYPE_OPERATOR_MUL:
			if (!(ast->left && token_flags_map[ast->left->token.type] & TOKEN_FLAG_IMPL_MUL_AFTER &&
				  ast->right && token_flags_map[ast->right->token.type] & TOKEN_FLAG_IMPL_MUL_BEFORE)) {
				chars_written += snprintf(string + chars_written, size_left - chars_written, "%s", token_str_repr_map[ast->token.type]);
			}
			break;

		case TOKEN_TYPE_ERR:
			m_stringify.is_error = true;
			memcpy(m_stringify.error_desc, ast->token.value.identifier, ast->token.value.identifier_len);
			m_stringify.error_desc_len = ast->token.value.identifier_len;
			return chars_written;

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

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_INFIX) && ast->right &&
		token_precedence_map[ast->token.type] <= token_precedence_map[ast->right->token.type] &&
		token_precedence_map[ast->right->token.type] != TOKEN_PRECEDENCE_NONE &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_ADD && ast->right->token.type == TOKEN_TYPE_OPERATOR_ADD) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_ADD && ast->right->token.type == TOKEN_TYPE_OPERATOR_SUB) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_SUB && ast->right->token.type == TOKEN_TYPE_OPERATOR_ADD) &&
		!(ast->token.type == TOKEN_TYPE_OPERATOR_MUL && ast->right->token.type == TOKEN_TYPE_OPERATOR_MUL)) {
		paren_precedence = true;
		chars_written += snprintf(string + chars_written, size_left - chars_written, "(");
	}

	if (ast->right) {
		chars_written += stringify_node(ast->right, string + chars_written, size_left - chars_written);
	}

	if ((token_flags_map[ast->token.type] & TOKEN_FLAG_PREFIX)) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, ")");
	}

	if (paren_precedence) {
		chars_written += snprintf(string + chars_written, size_left - chars_written, ")");
		paren_precedence = false;
	}

	return chars_written;
}

retval_t lang_stringify(ast_node_t *ast, char **string, int *str_len) {
	if (*string != NULL) {
		STRINGIFIER_FAIL_WITH_MSG("String output is not null");
	}

	static int max_str_len = 100;
	*string = calloc(1, max_str_len);
	if (*string == NULL) {
		STRINGIFIER_FAIL_WITH_MSG("Could not allocate memory for string");
	}

	m_stringify.is_error = false;

	*str_len = stringify_node(ast, *string, max_str_len);

	if (m_stringify.is_error) {
		memcpy(*string, m_stringify.error_desc, m_stringify.error_desc_len);
	}

	return RETVAL_OK;
}
