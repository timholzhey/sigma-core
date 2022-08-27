//
// Created by Tim Holzhey on 25.08.22.
//

#include <string.h>
#include <func_const.h>
#include "func_derive.h"
#include "derive_transform.h"

retval_t func_derive(ast_node_t *ast_in, ast_node_t *ast_out) {
	memcpy(ast_out, ast_in, sizeof(ast_node_t));

	func_const(ast_out, ast_out);

	return RETVAL_OK;
}

void func_derive_init() {
	derive_transform_init();
}
