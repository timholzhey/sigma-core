//
// Created by tholz on 27.08.2022.
//

#include <string.h>
#include "func_const.h"
#include "const_transform.h"
#include "logging.h"

static retval_t const_transform_node(ast_node_t *ast) {
	if (ast->left) {
		if (pattern_registry_apply_all(ast->left, &const_registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (ast->right) {
		if (pattern_registry_apply_all(ast->right, &const_registry) != RETVAL_OK) {
			return RETVAL_ERROR;
		}
	}

	if (pattern_registry_apply_all(ast, &const_registry) != RETVAL_OK) {
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

retval_t func_const(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	if (const_transform_node(ast_out) != RETVAL_OK) {
		log_error("Error during constant transform");
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

void func_const_init() {
	const_transform_init();
}
