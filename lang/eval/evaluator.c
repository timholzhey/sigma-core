//
// Created by Tim Holzhey on 23.08.22.
//

#include "evaluator.h"
#include "logging.h"
#include "func_derive.h"
#include "func_const.h"

retval_t lang_eval(ast_node_t *ast_in, ast_node_t *ast_out, sigma_function_t func) {
	switch (func) {
		case SIGMA_FUNCTION_DERIVE:
			return func_derive(ast_in, ast_out);

		case SIGMA_FUNCTION_CONST:
			return func_const(ast_in, ast_out);

		default:
			log_error("Unknown sigma function %u", func);
			return RETVAL_ERROR;
	}

	return RETVAL_OK;
}
