//
// Created by tholz on 28.08.2022.
//

#include "eval_transform.h"

retval_t eval_transform_node(ast_node_t *ast, pattern_registry_t *registry) {
	if (ast->left) {
		if (pattern_registry_apply_all(ast->left, registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (ast->right) {
		if (pattern_registry_apply_all(ast->right, registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (pattern_registry_apply_all(ast, registry) != RETVAL_OK) {
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}
