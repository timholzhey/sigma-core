//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_MATH_CORE_H
#define SIGMA_CORE_MATH_CORE_H

#include "sigma.h"
#include "math_lang_def.h"

typedef enum {
	MATH_FUNCTION_DERIVE,
	MATH_FUNCTION_CONST,
	MATH_FUNCTION_PLOT,
	MATH_FUNCTION_COUNT,
} math_function_t;

const char *derive(const char *func, char var);

void math_core_init();

retval_t math_parse(const char *func_str, char var, ast_node_t *ast);

const char *math_function(const char *func_str, char var, math_function_t sigma_func);

void debug_print_ast(ast_node_t *ast);

#endif //SIGMA_CORE_MATH_CORE_H
