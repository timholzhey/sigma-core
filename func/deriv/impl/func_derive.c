//
// Created by Tim Holzhey on 25.08.22.
//

#include <string.h>
#include "func_const.h"
#include "func_derive.h"
#include "derive_transform.h"
#include "logging.h"
#include "eval_transform.h"

retval_t func_derive(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	if (func_const(ast_out, ast_out) != RETVAL_OK) {
		log_error("Constant function failed");
		return RETVAL_ERROR;
	}

	if (eval_transform_node(ast_out, &derive_registry) != RETVAL_OK) {
		log_error("Error during derive transform");
		return RETVAL_ERROR;
	}

	if (func_const(ast_out, ast_out) != RETVAL_OK) {
		log_error("Second constant function failed");
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

void func_derive_init() {
	derive_transform_init();
}
