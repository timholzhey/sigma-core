//
// Created by tholz on 28.08.2022.
//

#include "logging.h"
#include "eval_transform.h"

retval_t eval_transform_node(ast_node_t *ast, pattern_registry_t *registry) {
	bool applied = false;

	if (ast->left) {
		if (eval_transform_node(ast->left, registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (ast->right) {
		if (eval_transform_node(ast->right, registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (pattern_registry_apply_all(ast, registry, &applied) != RETVAL_OK) {
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

retval_t eval_transform_function_node(ast_node_t *ast, pattern_registry_t *registry) {
	bool applied = false;

	if (pattern_registry_apply_all(ast, registry, &applied) != RETVAL_OK) {
		return RETVAL_ERROR;
	}

	if (applied) {
		return RETVAL_OK;
	}

	if ((ast->token.type == TOKEN_TYPE_OPERATOR_ADD || ast->token.type == TOKEN_TYPE_OPERATOR_SUB ||
		 ast->token.type == TOKEN_TYPE_OPERATOR_MUL) && ast->left && ast->right) {
		token_type_t left = ast->left->token.type;
		token_type_t right = ast->right->token.type;

		if (left == TOKEN_TYPE_NUM || ast->token.type != TOKEN_TYPE_OPERATOR_MUL) {
			if (eval_transform_function_node(ast->right, registry) != RETVAL_OK) {
				return RETVAL_ERROR;
			}
		}

		if (right == TOKEN_TYPE_NUM || ast->token.type != TOKEN_TYPE_OPERATOR_MUL) {
			if (eval_transform_function_node(ast->left, registry) != RETVAL_OK) {
				return RETVAL_ERROR;
			}
		}
	}

	return RETVAL_OK;
}
