//
// Created by Tim Holzhey on 25.08.22.
//

#include <string.h>
#include "func_derive.h"

retval_t func_derive(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));
	return RETVAL_OK;
}
