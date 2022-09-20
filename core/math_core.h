//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef SIGMA_CORE_MATH_CORE_H
#define SIGMA_CORE_MATH_CORE_H

typedef enum {
	MATH_FUNCTION_DERIVE,
	MATH_FUNCTION_CONST,
	MATH_FUNCTION_COUNT,
} math_function_t;

const char *derive(const char *func, char var);

void math_core_init();

const char *math_function(const char *func_str, char var, math_function_t sigma_func);

#endif //SIGMA_CORE_MATH_CORE_H
