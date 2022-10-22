//
// Created by Tim Holzhey on 20.09.22.
//

#include "sigma_lang_def.h"

const char *math_function_str_repr_map[MATH_FUNCTION_COUNT] = {
		[MATH_FUNCTION_DERIVE] = "func_derive",
		[MATH_FUNCTION_INTEGRATE] = "func_integrate",
		[MATH_FUNCTION_CONST] = "func_const",
		[MATH_FUNCTION_PLOT] = "func_plot",
};

const char *math_function_shorthand_str_repr_map[MATH_FUNCTION_COUNT] = {
		[MATH_FUNCTION_DERIVE] = "der",
		[MATH_FUNCTION_INTEGRATE] = "int",
		[MATH_FUNCTION_CONST] = "const",
		[MATH_FUNCTION_PLOT] = "plot",
};
