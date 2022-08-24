//
// Created by Tim Holzhey on 23.08.22.
//

#include "evaluator.h"
#include "logging.h"

retval_t evaluator_eval(ast_node_t *ast_in, ast_node_t *ast_out, sigma_function_t func) {
	switch (func) {
		case SIGMA_FUNCTION_DERIVE:
			break;

		default:
			log_error("Unknown sigma function %u", func);
			return RETVAL_ERROR;
	}

	return RETVAL_OK;
}
