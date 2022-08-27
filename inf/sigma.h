//
// Created by Tim Holzhey on 16.08.22.
//

#ifndef DERIVATIVE_CALCULATOR_MATHLANG_H
#define DERIVATIVE_CALCULATOR_MATHLANG_H

typedef enum {
	SIGMA_FUNCTION_DERIVE,
	SIGMA_FUNCTION_CONST,
	SIGMA_FUNCTION_COUNT,
} sigma_function_t;

const char *derive(const char *func, char var);

void sigma_init();

const char *sigma_function(const char *func_str, char var, sigma_function_t sigma_func);

#endif //DERIVATIVE_CALCULATOR_MATHLANG_H
