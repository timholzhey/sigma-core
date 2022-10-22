//
// Created by tholz on 22.10.2022.
//

#include <string.h>
#include "func_const.h"
#include "func_integrate.h"
#include "integrate_transform.h"
#include "logging.h"
#include "math_eval_transform.h"

retval_t func_integrate(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	if (func_const(ast_out, ast_out) != RETVAL_OK) {
		log_error("Constant function failed");
		return RETVAL_ERROR;
	}

	if (eval_transform_function_node(ast_out, &integrate_registry, true) != RETVAL_OK) {
		log_error("Error during integrate transform");
		return RETVAL_ERROR;
	}

	if (eval_transform_function_node(ast_out, &integrate_add_c_registry, true) != RETVAL_OK) {
		log_error("Error during integrate_add_c transform");
		return RETVAL_ERROR;
	}

	if (func_const(ast_out, ast_out) != RETVAL_OK) {
		log_error("Second constant function failed");
		return RETVAL_ERROR;
	}

	return RETVAL_OK;
}

void func_integrate_init() {
	integrate_transform_init();
}
