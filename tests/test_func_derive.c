//
// Created by tholz on 28.08.2022.
//

#include "testlib.h"
#include "math_lang_def.h"
#include <string.h>
#include "math_core.h"

TEST_DEF(test_func_derive, exponent_simple) {
	math_core_init();

	const char *func = "x^2";
	const char *expect_result = "2x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, exponent_simple2) {
	math_core_init();

	const char *func = "2*x^3";
	const char *expect_result = "6*x^2";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, sin) {
	math_core_init();

	const char *func = "sin(x)";
	const char *expect_result = "cos(x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, cos) {
	math_core_init();

	const char *func = "cos(x)";
	const char *expect_result = "-sin(x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, sin_add_constants) {
	math_core_init();

	const char *func = "sin(x)+5+2";
	const char *expect_result = "cos(x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_plus_constant) {
	math_core_init();

	const char *func = "x+2";
	const char *expect_result = "1";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_mult_constant) {
	math_core_init();

	const char *func = "2*x";
	const char *expect_result = "2";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_plus_var) {
	math_core_init();

	const char *func = "x+x";
	const char *expect_result = "2";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var_plus_var_power) {
	math_core_init();

	const char *func = "x+x^2";
	const char *expect_result = "2x+1";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, var) {
	math_core_init();

	const char *func = "x";
	const char *expect_result = "1";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, constant) {
	math_core_init();

	const char *func = "5";
	const char *expect_result = "0";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, log) {
	math_core_init();

	const char *func = "log(x)";
	const char *expect_result = "1/x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, sqrt) {
	math_core_init();

	const char *func = "sqrt(x)";
	const char *expect_result = "1/(2sqrt(x))";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, e_raise_x) {
	math_core_init();

	const char *func = "e^x";
	const char *expect_result = "e^x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, e_raise_x_power_2) {
	math_core_init();

	const char *func = "e^(x^2)";
	const char *expect_result = "e^(x^2)*2x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, e_raise_function) {
	math_core_init();

	const char *func = "e^(x+x^2)";
	const char *expect_result = "e^(x+x^2)*(2x+1)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, chain_simple) {
	math_core_init();

	const char *func = "sin(2x)";
	const char *expect_result = "2cos(2x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, chain_chain_simple) {
	math_core_init();

	const char *func = "sin(sin(x))";
	const char *expect_result = "cos(sin(x))*cos(x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, chain_chain_chain_simple) {
	math_core_init();

	const char *func = "sin(sin(sin(x)))";
	const char *expect_result = "cos(sin(sin(x)))*cos(sin(x))*cos(x)";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_DEF(test_func_derive, product_simple) {
	math_core_init();

	const char *func = "sin(x)*x";
	const char *expect_result = "sin(x)+cos(x)*x";

	const char *result = math_function(func, 'x', MATH_FUNCTION_DERIVE);

	TEST_ASSERT_EQ_STRING(result, expect_result, strlen(expect_result));
	TEST_ASSERT_EQ_U32(strlen(result), strlen(expect_result));

	TEST_CLEAN_UP_AND_RETURN(0);
}

TEST_RUNNER(test_func_derive) {
	TEST_REG(test_func_derive, exponent_simple);
	TEST_REG(test_func_derive, exponent_simple2);
	TEST_REG(test_func_derive, sin);
	TEST_REG(test_func_derive, cos);
	TEST_REG(test_func_derive, sin_add_constants);
	TEST_REG(test_func_derive, var_plus_constant);
	TEST_REG(test_func_derive, var_mult_constant);
	TEST_REG(test_func_derive, var_plus_var);
	TEST_REG(test_func_derive, var_plus_var_power);
	TEST_REG(test_func_derive, var);
	TEST_REG(test_func_derive, constant);
	TEST_REG(test_func_derive, log);
	TEST_REG(test_func_derive, sqrt);
	TEST_REG(test_func_derive, e_raise_x);
	TEST_REG(test_func_derive, e_raise_x_power_2);
	TEST_REG(test_func_derive, e_raise_function);
	TEST_REG(test_func_derive, chain_simple);
	TEST_REG(test_func_derive, chain_chain_simple);
	TEST_REG(test_func_derive, chain_chain_chain_simple);
	TEST_REG(test_func_derive, product_simple);
}
