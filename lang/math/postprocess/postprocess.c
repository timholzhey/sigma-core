//
// Created by Tim Holzhey on 30.08.22.
//

#include <string.h>
#include "postprocess.h"
#include "logging.h"

retval_t lang_postprocess(ast_node_t *ast_in, ast_node_t *ast_out) {
	if (ast_in == NULL || ast_out == NULL) {
		log_error("Invalid arguments");
		return RETVAL_ERROR;
	}

	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	// TODO: Sort powers

	return RETVAL_OK;
}
