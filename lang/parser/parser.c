//
// Created by Tim Holzhey on 16.08.22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#include "logging.h"

static struct {
	parser_error_t error;
	ast_node_t *fill;
} m_parser;

#define MAX_NESTING_LEVEL		1000

#define PARSER_FAIL_WITH_MSG(...) { \
	log_error_noterm("Parser failed with error: "); \
	log_error(__VA_ARGS__); \
	return RETVAL_ERROR; \
}

#define PARSER_HANDLE_MALLOC(expr) { \
	if ((expr) == NULL) {               \
        m_parser.error = PARSER_ERROR_MALLOC; \
    	PARSER_FAIL_WITH_MSG("Could not allocate memory"); \
	} \
}

retval_t lang_parse(token_t *tokens, int num_tokens, ast_node_t *ast) {
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
		m_parser.error = PARSER_ERROR_AST_NULL;
		PARSER_FAIL_WITH_MSG("AST is NULL");
	}

	ast_node_t *current;
	PARSER_HANDLE_MALLOC(current = calloc(1, sizeof(ast_node_t)));
	ast_node_t *nesting_stack[MAX_NESTING_LEVEL];
	uint32_t nesting_level = 0;
	bool begin_scope_prefixed = false;

	for (int token_pos = 0; token_pos < num_tokens; token_pos++) {
		token_t token = tokens[token_pos];

		// Case 1: Current token is unset
		if (current->token.type == TOKEN_TYPE_NONE) {
			// Check begin scope
			if (token_flags_map[token.type] & TOKEN_FLAG_BEGIN_SCOPE) {
				nesting_stack[nesting_level++] = current;
				continue;
			}

			memcpy(&current->token, &token, sizeof(token_t));
			continue;
		}

		// Case 2: Left child is unset
		if (current->left == NULL) {
			// Check begin scope was inferred by prefix
			if (begin_scope_prefixed && token_flags_map[token.type] & TOKEN_FLAG_BEGIN_SCOPE) {
				begin_scope_prefixed = false;
				continue;
			}

			PARSER_HANDLE_MALLOC(current->left = calloc(1, sizeof(ast_node_t)));
			memcpy(&current->left->token, &token, sizeof(token_t));

			// Check swap
			if (token_flags_map[token.type] & TOKEN_FLAG_INFIX ||
				token_flags_map[token.type] & TOKEN_FLAG_POSTFIX) {
				token_t tmp = current->token;
				current->token = current->left->token;
				current->left->token = tmp;
			}

			// Check finished
			if (token_flags_map[token.type] & TOKEN_FLAG_PREFIX ||
				token_flags_map[token.type] & TOKEN_FLAG_POSTFIX) {
				current->right = m_parser.fill;
			}

			continue;
		}

		// Case 3: Right child is unset
		if (current->right == NULL) {
			// Check surrounding
			if (token_flags_map[current->token.type] & TOKEN_FLAG_SURROUND) {
				if (current->token.type != token.type) {
					m_parser.error = PARSER_ERROR_SURROUNDING_MISMATCH;
					PARSER_FAIL_WITH_MSG("Surrounding tokens do not match: %s and %s",
						token_type_name_map[current->token.type], token_type_name_map[token.type]);
				}
				current->right = m_parser.fill;
				continue;
			}

			PARSER_HANDLE_MALLOC(current->right = calloc(1, sizeof(ast_node_t)));

			// Check begin scope
			if (token_flags_map[token.type] & TOKEN_FLAG_BEGIN_SCOPE) {
				nesting_stack[nesting_level++] = current;
				current = current->right;
				continue;
			}

			// Check end scope
			if (token_flags_map[token.type] & TOKEN_FLAG_END_SCOPE) {
				current = nesting_stack[--nesting_level];
				continue;
			}

			memcpy(&current->right->token, &token, sizeof(token_t));

			// Check prefix
			if (token_flags_map[token.type] & TOKEN_FLAG_PREFIX) {
				nesting_stack[nesting_level++] = current;
				current = current->right;
				begin_scope_prefixed = true;
				continue;
			}

			continue;
		}

		// Case 4: Both children are set
		if (token_flags_map[token.type] & TOKEN_FLAG_END_SCOPE) {
			current = nesting_stack[--nesting_level];
			continue;
		}
		if ((token_flags_map[token.type] & TOKEN_FLAG_INFIX) == 0 &&
			(token_flags_map[token.type] & TOKEN_FLAG_POSTFIX) == 0) {
			m_parser.error = PARSER_ERROR_UNEXPECTED_TOKEN;
			PARSER_FAIL_WITH_MSG("Unexpected token %s at position %d",
				token_type_name_map[token.type], token_pos);
		}

		ast_node_t *tmp = current;
		PARSER_HANDLE_MALLOC(current = calloc(1, sizeof(ast_node_t)));
		current->left = tmp;
		memcpy(&current->token, &token, sizeof(token_t));
	}

	// Check scope nesting
	if (nesting_level != 0) {
		m_parser.error = PARSER_ERROR_UNCLOSED_SCOPE;
		PARSER_FAIL_WITH_MSG("Unclosed scope");
	}

	// Copy root node to AST
	memcpy(ast, current, sizeof(ast_node_t));

	return RETVAL_OK;
}

parser_error_t parser_errno() {
	return m_parser.error;
}
