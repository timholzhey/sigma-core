//
// Created by tholz on 27.08.2022.
//

#include <string.h>
#include "math_eval_const.h"
#include "func_const.h"
#include "const_transform.h"
#include "logging.h"
#include "math_eval_transform.h"

#define NUM_ITER_CONST_TRANSFORM		5

retval_t func_const(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	for (int i = 0; i < NUM_ITER_CONST_TRANSFORM; i++) {
		if (eval_transform_node(ast_out, &const_registry) != RETVAL_OK) {
			log_error("Error during constant transform");
			return RETVAL_ERROR;
		}

		if (eval_const(ast_out) != RETVAL_OK) {
			log_error("Constant evaluation failed");
			return RETVAL_ERROR;
		}
	}

	return RETVAL_OK;
}

void func_const_init() {
	const_transform_init();
}
