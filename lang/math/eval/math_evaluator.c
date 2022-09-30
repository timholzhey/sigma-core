//
// Created by Tim Holzhey on 23.08.22.
//

#include "math_evaluator.h"
#include "logging.h"
#include "func_derive.h"
#include "func_const.h"

retval_t lang_eval(ast_node_t *ast_in, ast_node_t *ast_out, math_function_t func) {
	switch (func) {
		case MATH_FUNCTION_DERIVE:
			log_debug("Running math function: derive");
			return func_derive(ast_in, ast_out);

		case MATH_FUNCTION_CONST:
			log_debug("Running math function: const");
			return func_const(ast_in, ast_out);

		default:
			log_error("Unknown sigma function %u", func);
			return RETVAL_ERROR;
	}

	return RETVAL_OK;
}
